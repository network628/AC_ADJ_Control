
#include "config.h"

// U8 time_base_50us;
U8 time_base_1ms;
U8 time_base_10ms;

// 中断服务程序
void t2int() interrupt 12 // 中断入口
{
	// --time_base_50us;
	// if (time_base_50us == 0) // 10us*100=1ms
	{
		// time_base_50us = TIME_BASE_50US;

		if (hot_time > 0)//10us
			hot_time--;

		hot_handle();
	}

	--time_base_1ms;
	if (time_base_1ms == 0) // 10us*100=1ms
	{
		time_base_1ms = TIME_BASE_1MS;

		Disp_Num_Function();

		if (Light.counter > 0)
			Light.counter--;

		--time_base_10ms;
		if (time_base_10ms == 0) // 10us*100=1ms
		{
			time_base_10ms = TIME_BASE_10MS;
			Key_Scan_Cnt = 1; // 定时器变量1ms执行一次
		}
	}
}

//-----------------------------------------------
// #define FOSC 11059200L
// #define T2MS (65536 - FOSC / 1000) // 1T模式 1000us
//-----------------------------------------------
void Timer2_Init(void)
{
	AUXR |= 0x04; // 定时器2为1T模式
	//  AUXR &= ~0x04;//定时器2为12T模式
	// T2L = T2MS; // 初始化计时值
	// T2H = T2MS >> 8;

	T2L = 0x91;	  // 设置定时初始值 //10us
	T2H = 0xFF;	  // 设置定时初始值
	AUXR |= 0x10; // 定时器2开始计时

	IE2 |= 0x04; // 开定时器2中断
	EA = 1;
}
