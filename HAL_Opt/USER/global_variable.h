#ifndef __GLOBAL_VARIABLE_H__
#define __GLOBAL_VARIABLE_H__

#include "stdint.h"

uint32_t Timer_Fg;        //计时器重载累加值
uint32_t Timer_Fg1; 
uint8_t Blink_Id;       //点灯闪烁标识 1：闪烁 0：长亮
uint8_t Blink_Id_Old;   //上一次点灯闪烁标识
uint8_t BOARD_ADDRESS; //灯控板地址
uint8_t Can_Buff[8];    //CAN通讯解析后数据缓存
uint8_t Light_Buff[4]; //灯控板四个灯组的点灯信息缓存
uint8_t CAN_Send_Fg;   //CAN 发送flag
uint8_t CAN_Data_Read_Fg; //1：表示已经接收CAN数据至Can_Buff[8]； 0：与‘1’相反
uint8_t LED_FeedBack_Fg; //表示灯控板点灯是否需要反馈给主控板，1：是； 0：否

#endif
