#ifndef __GLOBAL_VARIABLE_H__
#define __GLOBAL_VARIABLE_H__

#include "stdint.h"

//外设句柄
CAN_HandleTypeDef CAN_Handle;
CAN_TxHeaderTypeDef CAN_TxHeader;
CAN_RxHeaderTypeDef CAN_RxHeader;

IWDG_HandleTypeDef IWDG_Handler;

TIM_HandleTypeDef TIM2_Handle;

uint32_t Sytem_Timer_Fg;        //计时器重载中断次数累加值; 与回码
uint32_t Sytem_Timer_Fg1;       //计时器重载中断次数累加值; 与CAN报文收取后点灯状态有关，如果闪烁，那么其值会降到10000内，若常亮超过2s后 其值在20000到30000内
uint8_t Blink_Id;               //点灯闪烁标识 1：闪烁 0：长亮
uint8_t Blink_Id_Before;        //上一次点灯闪烁标识
uint8_t Board_Address;          //灯控板地址
uint8_t CAN_Buff[8];            //CAN通讯解析后数据缓存
uint8_t Channel_State[4];       //灯控板四个灯组的点灯信息缓存
uint8_t CAN_Frame_ID;           //第几帧点灯指令
uint8_t CAN_DataRead_Fg;        //1：表示已经接收CAN数据至CAN_Buff[8]； 0：与‘1’相反
// uint8_t LED_VACheck_Fg;      //灯控板 当前点灯消息 标识符 由CAN报文解析出来,是否需要反馈给主控板，1：是； 0：否     // 暂时可以不需要，此段数据主要告诉电源板，在接管时，点灯情况
uint8_t VACheck_Fg;             //占比查询标识 为0时，需要查， 每次查询都 置1 TIM2每次中断都会置0
uint16_t CAN_Send_Wait_Time;    //灯控板按编号对应的回码时间
uint8_t CAN_VACheck_Send_Fg;    //灯控板点灯结果 CAN反馈标识

// 占比检查电压，电流次数统计
uint16_t Voltage_Count;
uint16_t Current_Count;
// 灯组1
uint16_t R1_Volatge_Count;
uint16_t R1_Current_Count;
uint16_t Y1_Volatge_Count;
uint16_t Y1_Current_Count;
uint16_t G1_Volatge_Count;
uint16_t G1_Current_Count;
uint8_t R1_Volatge_Fg;
uint8_t R1_Current_Fg;
uint8_t Y1_Volatge_Fg;
uint8_t Y1_Current_Fg;
uint8_t G1_Volatge_Fg;
uint8_t G1_Current_Fg;
// 灯组2
uint16_t R2_Volatge_Count;
uint16_t R2_Current_Count;
uint16_t Y2_Volatge_Count;
uint16_t Y2_Current_Count;
uint16_t G2_Volatge_Count;
uint16_t G2_Current_Count;
uint8_t R2_Volatge_Fg;
uint8_t R2_Current_Fg;
uint8_t Y2_Volatge_Fg;
uint8_t Y2_Current_Fg;
uint8_t G2_Volatge_Fg;
uint8_t G2_Current_Fg;
// 灯组3
uint16_t R3_Volatge_Count;
uint16_t R3_Current_Count;
uint16_t Y3_Volatge_Count;
uint16_t Y3_Current_Count;
uint16_t G3_Volatge_Count;
uint16_t G3_Current_Count;
uint8_t R3_Volatge_Fg;
uint8_t R3_Current_Fg;
uint8_t Y3_Volatge_Fg;
uint8_t Y3_Current_Fg;
uint8_t G3_Volatge_Fg;
uint8_t G3_Current_Fg;
// 灯组4
uint16_t R4_Volatge_Count;
uint16_t R4_Current_Count;
uint16_t Y4_Volatge_Count;
uint16_t Y4_Current_Count;
uint16_t G4_Volatge_Count;
uint16_t G4_Current_Count;
uint8_t R4_Volatge_Fg;
uint8_t R4_Current_Fg;
uint8_t Y4_Volatge_Fg;
uint8_t Y4_Current_Fg;
uint8_t G4_Volatge_Fg;
uint8_t G4_Current_Fg;


//函数声明

void Led_Init(void);
void Led_Display(void);
//led.c

void Board_Address_Init(void);
uint8_t Board_Address_Get(void);
//Board_Address.c

void OPT_CAN_Init(void);
void OPT_CAN_Send(unsigned int sid,unsigned char data[]);
//CAN.c

void IWDG_Init(uint8_t pre,uint_fast16_t reload);
void IWDG_Feed(void);
//IWDG.c

void TIM2_Init(uint16_t arr,uint16_t psc);
//TIM2.c

void VACheck_GPIO_Init(void);
void Clear_Check_Count(void);
void VACheck(void);
//VACheck.c

void System_Clock_Init(u32 pll);
//System_Clock.c
#endif
