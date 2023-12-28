/******************************************************************************
                                智信电子科技
******************************************************************************/

// SQUIRREL_STC12C5A60S2开发板例程
// 片内EEPROM驱动头文件
// R207SC@SQUIRREL_STC12C5A60S2





#ifndef     __STC_EEPROM_H__
#define     __STC_EEPROM_H__


//关闭IAP 功能, 清相关的特殊功能寄存器,使CPU 处于安全状态,
void IAP_Disable(void);
//读一字节，调用前需打开IAP 功能，入口:DPTR = 字节地址，返回:A = 读出字节
U8 Byte_Read(U16 add);
//字节编程，调用前需打开IAP 功能，入口:DPTR = 字节地址, A= 须编程字节的数据
void Byte_Program(U16 add, U8 ch);
//擦除扇区, 入口:DPTR = 扇区地址
void Sector_Erase(U16 add);



// 读取STC EEPROM
U8 STC_EE_Read(U16 Addr, U8 *Buf, U16 Num);
// 写入STC EEPROM
U8 STC_EE_Write(U16 Addr, U8 *Buf, U16 Num);

void PWM_Write_value(U16 dat);
U16 PWM_Read_value(void);

void Write_ON_OFF_Time(U16 dat);
U16 Read_ON_OFF_Time(void);


#endif // end of __STC_EEPROM_H__














