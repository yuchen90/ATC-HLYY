#ifndef __GLOBAL_VARIABLE_H__
#define __GLOBAL_VARIABLE_H__

#include "stdint.h"

uint32_t Timer_Fg;        //计时器重载中断次数累加值; 与回码
uint32_t Timer_Fg1;       //计时器重载中断次数累加值; 与CAN报文收取后点灯状态有关，如果闪烁，那么其值会降到10000内，若常亮超过2s后 其值在20000到30000内
uint8_t Blink_Id;       //点灯闪烁标识 1：闪烁 0：长亮
uint8_t Blink_Id_Old;   //上一次点灯闪烁标识
uint8_t BOARD_ADDRESS; //灯控板地址
uint8_t Can_Buff[8];    //CAN通讯解析后数据缓存
uint8_t Light_Buff[4]; //灯控板四个灯组的点灯信息缓存
uint8_t CAN_Send_Fg;   //CAN 发送flag
uint8_t CAN_Data_Read_Fg; //1：表示已经接收CAN数据至Can_Buff[8]； 0：与‘1’相反
uint8_t LED_FeedBack_Fg; //表示灯控板点灯是否需要反馈给主控板，1：是； 0：否
uint8_t LED_Check_Fg;    //灯控板 当前点灯消息 标识符 ？？？？？？需理解含义

//函数声明
//led.c
void Led_Init(void);
void Led_Display(void);
//Board_Address.c
void Board_Address_Init(void);
uint8_t Board_Address_Get(void);
//CAN.c
void OPT_CAN_Init(void);
void OPT_CAN_Send(unsigned int SID,unsigned char data[]);
//IWDG.c
void IWDG_Init(uint8_t pre,uint_fast16_t reload);
void IWDG_Feed(void);
//TIM2.c
void TIM2_Init(uint16_t arr,uint16_t psc);
//VACheck.c
void VACheak_GPIO_Init(void);

#endif
