
#include "config.h"

void NoCall_Uart(void);

//=============================================================================

//=============================================================================
#define URBMax 20

U8 UartRecvBuf[URBMax]; //
U8 URWP = 0;            //
U8 URRP = 0;            //
U8 URNum = 0;           //

#define USBMax 20 //

U8 UartSendBuf[URBMax]; //
U8 USWP = 0;            //
U8 USRP = 0;            //
U8 USNum = 0;           //

U8 SendFlag = 0;

//
U8 URQWrite(U8 Data)
{ 
    if (URNum >= URBMax)
        return FALSE;         //
    UartRecvBuf[URWP] = Data; //
    URWP++;                   //
    if (URWP >= URBMax)
    {
        URWP = 0;
    }
    URNum++;
    return TRUE; //
}

U8 URQRead(U8 *Data)
{
    if (URNum == 0)
        return FALSE;          //
    ES = 0;                    // 
    *Data = UartRecvBuf[URRP]; //
    URRP++;                    //
    if (URRP >= URBMax)
    {
        URRP = 0;
    }
    URNum--;
    ES = 1;      //
    return TRUE; //
}

U8 USQWrite(U8 Data)
{
    if (USNum >= USBMax)
        return FALSE;         //
    ES = 0;                   //
    UartSendBuf[USWP] = Data; //
    USWP++;                   //
    if (USWP >= USBMax)
    {
        USWP = 0;
    }
    USNum++;
    if (SendFlag == 0) //
    {
        TI = 1; //
    }
    ES = 1;      //
    return TRUE; //
}

//
U8 USQRead(U8 *Data)
{
    if (USNum == 0)
        return FALSE;          //
    *Data = UartSendBuf[USRP]; //
    USRP++;                    //
    if (USRP >= USBMax)
    {
        USRP = 0;
    }
    USNum--;
    return TRUE; //
}
//=============================================================================
// KEIL printf
//=============================================================================
char putchar(char chr)
{ 
    while (USQWrite(chr) == FALSE)
        ;
    return (chr);
}

char _getkey()
{
    char Data; 
    while (URQRead((U8 *)&Data) == FALSE)
        ;
    return Data;
}
 
//=============================================================================
//
//=============================================================================

//
void UART_SendChar(U8 chr)
{ 
    while (USQWrite(chr) == FALSE)
        ;
}
 
void UART_SendString(U8 *str)
{
    while (*str)
    {
        UART_SendChar(*str++);
    }
}
 
U8 UART_RecvChar(void)
{
    U8 Data;
    //
    while (URQRead(&Data) == FALSE)
        ;
    return Data;
}
 
U8 UART_RecvChar_N(U8 *Data)
{
    return URQRead(Data);
}

U16 Receive_Cnt;
void UartInit(void)
{
    SCON = 0x50;
    AUXR |= 0x01;
    AUXR |= 0x04;
    T2L = 0xE0;   // 11.0592M 9600
    T2H = 0xFE;   //
    AUXR |= 0x10; //
    ES = 1;       //
    REN = 1;      //
    SM0 = 0;      // SM0 SM1
    SM1 = 1;

    TI = 0;       
    //ES = 1;             
    //EA = 1;            
    NoCall_Uart(); //
    Receive_Cnt = 0;
}

//=============================================================================
//=============================================================================
void UART_Interrupt_Receive(void) interrupt 4
{
    U8 Data;

    if (RI == 1)
    {
        RI = 0;
        Data = SBUF;    //
        URQWrite(Data); //
        Receive_Cnt++;
        Light.counter = 40;
    }
    if (TI == 1)
    {
        TI = 0;
        if (USQRead(&Data) == TRUE) //
        {
            SBUF = Data;  //
            SendFlag = 1; //
        }
        else
        {
            SendFlag = 0; //
        }
    }
}

//=============================================================================

//=============================================================================
void NoCall_Uart(void)
{
    U8 i;
    i = 0;
    if (i)
    {
        // Uart.c
        // KEIL printf
        putchar(0);
        _getkey();
        //
        UART_SendChar(0);
        //
        UART_SendString((U8 *)0);
        //
        UART_RecvChar();
        //
        UART_RecvChar_N((U8 *)0);
    }
}
//=============================================================================

#define DATA_HEADER 0x41 // 假设数据头为0x41
// #define DATA_TAIL 0x7E    // 假设数据尾为0x7E
#define EXPECTED_DATA_LENGTH 20 // 假设的数据长度
// 检查数据是否完整
U8 IsDataComplete(U8 *dat, U8 length)
{
    // 首先检查数据长度
    // if (length != EXPECTED_DATA_LENGTH) {
    //     return 0;
    // }

    // 然后检查数据头
    if (dat[0] != DATA_HEADER || length == EXPECTED_DATA_LENGTH)
    {
        return 0;
    }

    // // 检查数据尾
    // if (data[length - 1] != DATA_TAIL) {
    //     return 0;
    // }

    // // 进行校验和计算（此处需要您根据实际的校验和算法进行实现）
    // U8 checksum = CalculateChecksum(data, length);
    // if (data[length - 2] != checksum) {
    //     return 0;
    // }

    return 1; // 数据完整
}

void ProcessLightControl(U8 *dat)
{
    // 确认数据是否符合特定的模式
    // 41 54 2B 52 53 50 43 04 02 06 01 80
    if ((dat[0] == 0x41) && (dat[1] == 0x54) && (dat[2] == 0x2B) && (dat[3] == 0x52) && (dat[4] == 0x53) && (dat[5] == 0x50) && (dat[6] == 0x43) && (dat[7] == 0x03))
    {
        // 此处处理灯光控制逻辑
        // ...

        if (dat[10] != 0 && Light.sw_flag == 0)
        {
            INT1_init(1);
            P1 = 0x00;
            Light.sw_flag = 1;
            Light.ON_Time = 0;
            Light.AC_Voltage = dat[10] - 128;
            // Light.AC_Voltage = PWM_Read_value();
            DlyMs(50);
            Write_ON_OFF_Time(Light.ON_Time);
        }
        else if (dat[10] == 0 && Light.sw_flag != 0)
        {
            INT1_init(0);
            P1 = 0x00;
            Light.sw_flag = 0;
            Light.ON_Time = 0;
            PWM_Write_value(Light.AC_Voltage);
            DlyMs(50);
            Write_ON_OFF_Time(Light.ON_Time);
        }
        else if ((dat[10]) >= 0x01 && (dat[10]) <= 0x7F && Light.sw_flag == 1)
        {
            Light.AC_Voltage = (float)(dat[10] * 2 * 0.86);
        }
        Light.L_value = 221 - Light.AC_Voltage;
    }
}

U8 ReceiveData[20];
void Uart_Contorl(void) 
{
    U8 process_length = 0;
    U8 i;
    U8 Dat;
    if (Light.counter == 0 && Receive_Cnt != 0)
    {
        while (URQRead(&Dat))
        {
            if (process_length < sizeof(ReceiveData))
            {
                ReceiveData[process_length++] = Dat;
            }
            else
            {
                break;
            }
        }

        if (IsDataComplete(ReceiveData, process_length))
        {
            ProcessLightControl(ReceiveData);
        }

        // 发送数据
        for (i = 0; i < process_length; i++)
        {
            UART_SendChar(ReceiveData[i]);
            ReceiveData[i] = 0;
        }
        process_length = 0;
        Receive_Cnt = 0;
    }
}
 