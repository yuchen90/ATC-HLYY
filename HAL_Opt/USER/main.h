//声明需要使用的全局变量
#ifndef __MAIN_H__
#define __MAIN_H__

extern unsigned int Timer_Fg;        //计时器重载累加值
extern unsigned int Timer_Fg1; 
extern unsigned char Blink_Id;       //点灯闪烁标识 1：闪烁 0：长亮
extern unsigned char Blink_Id_Old;   //上一次点灯闪烁标识
extern unsigned char BOARD_ADDRESS; //灯控板地址
extern unsigned char Can_Buff[8];    //CAN通讯解析后数据缓存
extern unsigned char Light_Buff[4]; //灯控板四个灯组的点灯信息缓存
extern unsigned char CAN_Send_Fg;   //CAN 发送flag

//函数声明
//led.c
void Led_Init(void);
void Light(void);
//Board_Address.c
void Board_Address_Init(void);
uint8_t Board_Address_Get(void);
//CAN.c
void OPT_CAN_Init(void);
void OPT_CAN_Send(uint32_t SID,uint8_t data[8]);

#endif
