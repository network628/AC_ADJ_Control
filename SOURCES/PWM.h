
#ifndef     __PWM_H__
#define     __PWM_H__
#include "config.h"
/*
	单片机白炽灯调光程序 (晶振:11.0592MHz) 
*/ 
 
extern uint16_t hot_time;

void INT0_init(void);
void INT1_init(bit en);
void hot_handle(void);

#endif
