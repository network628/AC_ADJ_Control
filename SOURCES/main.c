

#include "config.h"

void NO_CALL(void);
void Matched_Process(void);

struct LIGNT Light;

void main(void)
{
	NO_CALL();
	INT0_init();
	Timer2_Init();
	UartInit();
	Matched_Process();

	while (1)
	{
		key_handle();
		Uart_Contorl();
	}
}

void NO_CALL(void)
{
	P1M0 = 0x00;
	P1M1 = 0x00;
	P3M0 = 0x00;
	P3M1 = 0x00;
	Light.sw_flag = 0;
	Light.counter = 0;
	// Light.time_value = 1;
//	time_base_50us = TIME_BASE_50US;
	time_base_1ms = TIME_BASE_1MS; 
}

// 41 54 2B 54 59 50 45 11 AC（44049-- AC11） 风扇的品类
// 41 54 2B 54 59 50 45 29 A8 (43049 A829)   单白光的品类
// U8 ID_Str[] = {0x41,0x54,0x2B,0x54,0x59,0x50,0x45,0x29,0xA8,"\r\n"};  //ID_str
U8 ID_Str[] = {0x41, 0x54, 0x2B, 0x54, 0x59, 0x50, 0x45, 0x29, 0xA8, "\r\n"}; // ID_str
U8 RST_Str[] = {"AT+PAIRSTART\r\n"};										  //
U8 PAIRSAVE_Str[] = {"AT+PAIRSAVE\r\n"};									  //
U8 RESTORE_Str[] = {"AT+RESTORE\r\n"};
void Matched_Process(void)
{
	Light.ON_Time = Read_ON_OFF_Time(); //
	printf("Light.ON_Time=%d\r\n", Light.ON_Time);
	Light.ON_Time++;
	DlyMs(10);

	if (Light.ON_Time == 4)
	{
		UART_SendString(RESTORE_Str); //
		DlyMs(500);
		Light.ON_Time -= 2;
		while (Light.ON_Time--)
		{

			UART_SendString(ID_Str); //
			DlyMs(500);

			disp_num = 888;
			UART_SendString(RST_Str); //
			DlyMs(500);

			disp_num = 0;
			DlyMs(500);
		}

		Light.ON_Time = 0;
		DlyMs(10000);
		UART_SendString(PAIRSAVE_Str);
		DlyMs(10);
		UART_SendString(PAIRSAVE_Str);
		DlyMs(10);
	}

	Write_ON_OFF_Time(Light.ON_Time);
}

/**************************************************************************/

/**************************************************************************/
