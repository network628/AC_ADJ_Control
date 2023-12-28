/******************************************************************************
                                閺呰桨淇婇悽闈涚摍缁夋垶濡?
******************************************************************************/

// SQUIRREL_STC12C5A60S2瀵?鈧?閸欐垶婢?
// 婢跺瓨鏋冩禒鍫曟肠閸氾拷 閸欙拷 娑撯偓娴滄盯鍘ょ純顔讳繆閹?锟?  
// R207SC@SQUIRREL_STC12C5A60S2



#ifndef     __CONFIG_H__
#define     __CONFIG_H__


#ifndef TRUE
# define TRUE       1
#endif

#ifndef FALSE
# define FALSE      0
#endif

#ifndef NULL
# define NULL       0
#endif
 
typedef unsigned char   U8;
typedef signed   char   S8;
typedef unsigned int    U16;
typedef signed   int    S16;
typedef unsigned long   U32;
typedef signed   long   S32;

// typedef unsigned char uint8;
// typedef unsigned short uint16;
// typedef unsigned int uint24;
// typedef unsigned long uint32;

#define uint8_t unsigned char
#define u8 unsigned char
#define u16 unsigned short
#define uint16_t unsigned short
#define u32 unsigned int

#include <stdio.h>
#include <intrins.h>
#include "STC15W.h"
#include "Uart.H"
#include "STCEEPROM.H"
#include "PWM.H"
#include "LED3.H"
#include "timer.h"
#include "key.h"

extern struct LIGNT{ 
	U8 sw_flag;	        //开关变量 0:关机   1：开机
	U16 L_value;	    //0-255	   亮度值变量
	U16 AC_Voltage;	    //交流电压
	U16 ON_Time;		//开关次数	
    U16 counter;		//超过40ms没有新的串口数据就可以处理了
	// U16	time_value;		//预设定时器初值
	// U16 Initial_Value; 	//定时器初值
    // U8 INT0_flag;
	// U8 timer0_interrupt;
}Light; 

sbit lamp_pwm = P3^4;   

sbit key_up   = P5^4;  
sbit key_down = P5^5;  
sbit key_sw   = P3^2;  

#endif // end of __CONFIG_H__











