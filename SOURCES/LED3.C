#include "config.h"

// https://blog.csdn.net/weixin_46364710/article/details/114939283
U8 X;
U16 disp_num;
void Disp_Num_Function(void) //
{
	//		   P17 P16 P15 P14 P13 P12 P11 P10
	//		   DB   G	F	E	D	C	B	A
	//             0    1    2    3    4    5    6    7    8    9
	U8 LED[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

	switch (X)
	{
	case 0:
		P37 = 0;
		P36 = 1;
		P35 = 1;
		P1 = LED[(disp_num % 1000) / 100];
		break;
	case 1:
		P37 = 1;
		P36 = 0;
		P35 = 1;
		P1 = LED[(disp_num % 1000) % 100 / 10];
		break;
	case 2:
		P37 = 1;
		P36 = 1;
		P35 = 0;
		P1 = LED[disp_num % 10];
		break;
	}
	X = ++X % 3;
}

// void delay_us(U16 t)
//{
//	 U16 i;
//	 for(i=0;i<t;i++)
//	 {
//	   _nop_();
//	 }
// }

void DlyMs(U16 t) //@22.1184MHz
{
	U8 i, j;

	if (t == 0)
		return;
	do
	{
		i = 11;
		j = 159;
		do
		{
			while (--j)
				;
		} while (--i);
	} while (--t);
}