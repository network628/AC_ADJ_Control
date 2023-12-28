
#include "config.h"
 
uint16_t hot_time;
uint16_t adj_time_Max; //(100-1)
uint16_t adj_time_Min;
uint16_t ADJ_Value;
float FtimeMin;

void INT1s() interrupt 2 using 3 // 50HZ_INT1的中断服务函数
{
	hot_time = 260;

	if (Light.sw_flag)
	{ //
		Light.AC_Voltage = Light.L_value;
		if (Light.AC_Voltage > 220)
			Light.AC_Voltage = 220;
		disp_num =  Light.AC_Voltage;
		ADJ_Value = Light.L_value;

		FtimeMin = (ADJ_Value * 1.3);
		adj_time_Max = FtimeMin + 4;
		adj_time_Min = 2; // 20
	}
}

//==============================================================================
//	Function: hot_handle
//		Input: None
//		Output: None
//==============================================================================
void hot_handle(void)
{
	// 500~2
	if ((hot_time < adj_time_Max) && (hot_time > adj_time_Min))
	// if ((hot_time < 500) && (hot_time > 490))//10=217us
	// if ((hot_time < 30) && (hot_time > 20))
	{
		lamp_pwm = 0; // HOT_ENABLE;
	}
	else
		lamp_pwm = 1; // HOT_DISABLE;
}

void timer0() interrupt 1 // 定时器0的中断服务函数
{
}
/********************************************/
void exint0() interrupt 0 // INT0的中断服务函数
{
}

void INT0_init(void)
{
	IT0 = 1;
	EX0 = 1;
	EA = 1;
}

void INT1_init(bit en) // 1 open    0 off
{
	TMOD |= 0x01;
	IT1 = 1; //

	if (en)
	{
		EX1 = 1; //
		ET0 = 1; //
	}
	else
	{
		EX1 = 0; //
		ET0 = 0; //
	}
	EA = 1;
}
