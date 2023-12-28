//==============================================================================
//	Include Header Files
//==============================================================================
#include "config.h"

bit Key_Scan_Cnt; // 定时器变量1ms执行一次
KeyValue_ENUM key;
// 按键扫描
KeyValue_ENUM KeyScan(void)
{
	uint8_t io_value;
	static uint8_t key_Press; // 这个是要返回的键值
	static uint8_t key_Old = 0x00;
	static uint8_t DownCnt = 0; // 按下计数
	static uint8_t CntLongPress = 0;
	static struct _sta
	{
		uint8_t up : 1; // 弹起
		uint8_t dn : 1; // 按下
		uint8_t rep : 1;
	} Status; // 按键状态标记
	uint8_t ret;

	io_value = 0x00;
	ret = KEY_OFF;

	// 获取当前按下的按键
	if (!key_sw)
		io_value |= KEY_S1;
	if (!key_up)
		io_value |= KEY_S2;
	if (!key_down)
		io_value |= KEY_S3;

	// if (!Key4_ReadSta())io_value |= KEY_S4;

	if (io_value) // 如果按键被按下
	{
		if (key_Old == io_value) // 判断与上次扫描到的是否为同一个按键
		{
			DownCnt++; // 计数

			if (DownCnt < KEY_DOWN_CNT) // 当前计数小于长按的时间
			{
				if (Status.rep == 0) // 不是重复
				{
					Status.dn = 1;
					key_Press = io_value; // 记下按键
				}
			}

			if (DownCnt >= KEY_DOWN_CNT) // 当前计数大于长按的时间
			{
				Status.rep = 1; // 标记重复

				if (CntLongPress++ == KEY_REP_3S) // 按下超过3秒
				{
					ret = io_value | KEY_LONG_FLAG; // 加长按标记
				}
				else
				{
					ret = io_value | KEY_REP_FLAG; // 重复
				}

				DownCnt = KEY_SPEED_CNT; // 重复起始值
			}
		}
		key_Old = io_value; // 记录键值
	}
	else // 按键松开
	{
		if (Status.dn && !Status.rep) // 返回松开前的键值
		{
			ret = key_Press;
		}

		// 清除标记
		Status.dn = 0;
		Status.rep = 0;
		DownCnt = 0;
		CntLongPress = 0;
		key_Old = KEY_NO;
	}

	return (KeyValue_ENUM)ret; // 返回键值
}
//--------------END OF FILE---------------

//==============================================================================
//	Function: key_handle
//		Input: None
//		Output: None
//==============================================================================
void key_handle(void)
{
	if (Key_Scan_Cnt == 0)
		return;
	Key_Scan_Cnt = 0;

	key = KeyScan(); // 获取按下的按键值
	switch (key)
	{
	case KEY_Switch: //
		if (Light.sw_flag)
		{
			Light.sw_flag = 0; // 0:关机 
			INT1_init(0);
			disp_num = 0;
			PWM_Write_value(Light.AC_Voltage);
		}
		else
		{
			Light.sw_flag = 1; // 1：开机
			Light.AC_Voltage = PWM_Read_value();
			disp_num = Light.AC_Voltage;
			Light.L_value = Light.AC_Voltage; 
			INT1_init(1);
		}
		Light.ON_Time = 0;
		Write_ON_OFF_Time(Light.ON_Time); //
		break;
	case KEY_UUp:		   //
		if (Light.sw_flag) //
		{
			Light.L_value += 2;
			if (Light.L_value > 220)
			{
				Light.L_value = 220;
			}
		}
		break;
	case KEY_DDown: //
		if (Light.sw_flag) //
		{
			Light.L_value -= 2;
			if (Light.L_value < 2)
			{
				Light.L_value = 1;
			}
		}
		break;
		case KEY_L_UP:		   //
		if (Light.sw_flag) //
		{
			Light.L_value += 20;
			if (Light.L_value > 200)
			{
				Light.L_value = 200;
			}
		}
		break;
	case KEY_L_DN: //
		if (Light.sw_flag) //
		{
			Light.L_value -= 20;
			if (Light.L_value < 20)
			{
				Light.L_value = 20;
			}
		}
		break;
	}
}
