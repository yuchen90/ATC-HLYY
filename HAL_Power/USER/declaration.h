#ifndef __DECLARARTION_H
#define __DECLARARTION_H
//extern 引用 global_variable.h 声明的函数或全局变量

#include "stdint.h"
#include "stm32f1xx_hal.h"

//外设句柄
    extern UART_HandleTypeDef POWER_UART2_Handle;
    extern uint8_t UART_Rx_Buff[UART2_RxDataSize];
    extern DMA_HandleTypeDef UART2Rx_DMA_Handle;
    extern DMA_HandleTypeDef UART2Tx_DMA_Handle;

    extern CAN_HandleTypeDef CAN_Handle;
    extern CAN_TxHeaderTypeDef CAN_TxHeader;
    extern CAN_RxHeaderTypeDef CAN_RxHeader;

    extern TIM_HandleTypeDef TIM2_Handle;
//系统变量
    extern uint32_t System_Time_Fg;                                      //TIM2中断（100us一次）++； TFg(TimeFlag 缩写)
    extern uint32_t System_Time_Fg1;                                     //灯控板闪烁先亮后灭时，置0.
    extern uint32_t CAN_DataRead_Fg;                                    //主控板发给灯控板发送点灯数据，电源板接收到的标识符

// CAN消息buff
    //一般信息
    extern uint8_t CAN_Id_CANType;                                      //通过CAN的ID解析出协议定义的CAN类型
    extern uint8_t CAN_FrameNumber;                                     //标准帧：主控板发送给灯控板点灯数据 第几包；    扩展帧：接管信息 帧序号
    
    //灯控板点灯信息
    extern uint8_t CAN_Buff[16];                                        //两包主控板发给灯控板点灯数据接收缓存
    extern uint8_t CMD[15];                                             //接管信息 点灯指令
    extern uint8_t Blink_Id;                                            //点灯信息，闪烁灯是否亮起标识， 0：灭； 1：亮
    extern uint8_t Blink_Id_Before;                                     //上一次闪烁标识
    extern uint8_t Opt_CheckReply_Fg;                                   //灯控板点灯反馈标识，缓存
    extern uint8_t Opt_CheckReply_1st;                                  //第一包数据灯控板点灯反馈标识
    extern uint8_t Opt_CheckReply_2nd;                                  //第二包数据灯控板点灯反馈标识
    extern uint8_t Opt_BoardId;                                         //灯控板编号
    
    //电源板
    extern uint8_t Power_Reply_Fg;                                      //电源板反馈信息标识
    
    //接管信息
    extern uint32_t CheckSum;                                           //接管信息的4字节校验值
    extern uint16_t ArrayNum;                                           //接管信息 接管数据个数
    extern uint16_t FrameNum;                                           //接管信息 之后接收的帧个数
   
    extern struct TakeOver_Structure TakeOver_Structure_Use[160];       //接管信息 最终使用信息
    extern struct TakeOver_Structure TakeOver_Structure_Buff[160];      //接管信息 信息接收缓存
    extern uint16_t TakeOver_Pointer;                                   //接管信息数据指针
    extern uint16_t TakeOver_DataNum;                                   //接管信息数据个数（总节拍数）  拷贝 ArrayNum
    extern uint8_t RunTime;                                             //电源板接管时，当前节拍的点灯持续时间

    //市电检测
    extern uint8_t JSY_MK163_ReadBuff[20];                              //市电感应读取数据缓存
    extern uint8_t JSY_MK163_ReadNum;                                   //市电感应读取数据 元素索引
    extern uint16_t JSY_MK163_ReadRequest_Fg;                           //市电感应信息查询动作标识， 每秒查询1次，每次接收完整点灯信息帧加1，大于等于4时，置0
    extern uint8_t UART_Send_Buff[UART2_TxDataSize];

    //检测信息(主控板->电源板)
    extern uint8_t TakeOver_Enable;                                     //是否需要接管
    extern uint8_t YBlink_Enable;                                       //是否要硬黄闪
    extern uint8_t Error_YBlink_Enable;                                 //异常是否硬黄闪
    extern uint8_t Opt_VCheck_Enable;                                   //灯控板是否需电压检测
    extern uint8_t Opt_ACheck_Enable;                                   //灯控板是否需电流检测
    
    //灯控板反馈信息
    extern struct Opt_Light_Reply_Structure Opt_Reply_Buff[10];         //灯控板反馈点灯信息缓存,10块板子
    extern struct Opt_Light_Reply_ResultCount Opt_Reply_State[10];      //灯控板反馈点灯信息内容，10块板子
    
//硬黄闪信息 ??
    extern uint16_t YBlink_Count1;                                      //处于硬黄闪计数
    extern uint16_t YBlink_Count2;                                      //非硬黄闪计数
    extern uint16_t YBlink_Count3;                                      //处于硬黄闪计数
    extern uint16_t YBlink_Count4;                                      //非硬黄闪计数
    extern uint8_t YBlink_Fg;                                           //

//DEBUG 参数
    extern uint32_t w,e,t,r;
#endif
