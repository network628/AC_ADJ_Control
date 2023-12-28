 
#ifndef     __UART_H__
#define     __UART_H__

#include "config.h"

#ifndef TURE
 #define TRUE              1
#endif

#ifndef FALSE
 #define FALSE             0
#endif

//=============================================================================
// KEIL printf 接口部分
//=============================================================================
char putchar (char chr);  
char _getkey ();  

//=============================================================================
// 用户界面部分
//=============================================================================
U8  URQRead(U8 *Data);

// 串口发送字符
void UART_SendChar(U8 chr);
// 串口发送字符串
void UART_SendString(U8 *str);
//void UART_Send_ACk(U8 *str,U8 n);
// 从串口接收字符 阻塞
U8  UART_RecvChar(void);
// 从串口接收字符 非阻塞
U8  UART_RecvChar_N(U8 *Data);
// 串口初始化
void UartInit(void);
 
void Uart_Contorl(void);


#endif // end of __UART_H__





