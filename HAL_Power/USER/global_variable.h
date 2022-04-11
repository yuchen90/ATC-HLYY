#ifndef __GLOBAL_VARIABLE_H__
#define __GLOBAL_VARIABLE_H__
//全局变量 和 函数 声明
#include "stdint.h"
#include "stm32f1xx_hal.h"

//外设句柄
    UART_HandleTypeDef POWER_UART2_Handle;
    uint8_t UART_Rx_Buff[UART2_RxDataSize];
    DMA_HandleTypeDef UART2Rx_DMA_Handle;
    DMA_HandleTypeDef UART2Tx_DMA_Handle;

    CAN_HandleTypeDef CAN_Handle;
    CAN_TxHeaderTypeDef CAN_TxHeader;
    CAN_RxHeaderTypeDef CAN_RxHeader;
    CAN_RxHeaderTypeDef CAN_RxHeader1;

    TIM_HandleTypeDef TIM2_Handle;

    IWDG_HandleTypeDef IWDG_Handle;

//系统变量
    uint32_t System_Time_Fg;                                    //TIM2中断（100us一次）++； TFg(TimeFlag 缩写)
    uint32_t System_Time_Fg1;                                   //灯控板闪烁先亮后灭时，置0.
    uint32_t CAN_DataRead_Fg;                                   //主控板发给灯控板发送点灯数据，电源板接收到的标识符

// CAN消息buff
    //一般信息
    uint8_t CAN_Id_CANType;                                     //通过CAN的ID解析出协议定义的CAN类型
    uint8_t CAN_FrameNumber;                                    //标准帧：主控板发送给灯控板点灯数据 第几包；    扩展帧：接管信息 帧序号
    
    //灯控板点灯信息
    uint8_t CAN_Buff[16];                                       //两包主控板发给灯控板点灯数据接收缓存
    uint8_t CMD[15];                                            //接管信息 点灯指令
    uint8_t Blink_Id;                                           //点灯信息，闪烁灯是否亮起标识， 0：灭； 1：亮
    uint8_t Blink_Id_Before;                                    //上一次闪烁标识
    uint8_t Opt_CheckReply_Fg;                                  //灯控板点灯反馈标识，缓存
    uint8_t Opt_CheckReplyState_1st;                            //第一包数据灯控板点灯反馈标识，不用每块灯控板保存一次，凡是需要点灯反馈，所有通道都要求反馈（即使是灭灯）
    uint8_t Opt_CheckReplyState_2nd;                            //第二包数据灯控板点灯反馈标识
    uint8_t Opt_BoardId;                                        //灯控板编号
        
    //接管信息
    uint32_t CheckSum;                                          //接管信息的4字节校验值
    uint16_t ArrayNum;                                          //接管信息 接管数据个数，二分之一 FrameNum
    uint16_t FrameNum;                                          //接管信息 之后接收的帧个数
   
    struct TakeOver_Structure TakeOver_Structure_Use[160];      //接管信息 最终使用信息
    struct TakeOver_Structure TakeOver_Structure_Buff[160];     //接管信息 信息接收缓存
    uint16_t TakeOver_Pointer;                                  //接管信息数据指针
    uint16_t TakeOver_DataNum;                                  //接管信息数据个数（总节拍数）  拷贝 ArrayNum
    uint8_t RunTime;                                            //电源板接管时，当前节拍的点灯持续时间

    //市电检测
    uint8_t JSY_MK163_ReadBuff[20];                             //市电感应读取数据缓存
    uint8_t JSY_MK163_ReadNum;                                  //市电感应读取数据 元素索引
    uint16_t JSY_MK163_ReadRequest_Fg;                          //市电感应信息查询动作标识， 每秒查询4次，每次接收完整点灯信息帧加1，大于等于4时，置0
    uint8_t UART_Send_Buff[UART2_TxDataSize] = {0x01,0x03,0x00,0x48,0x00,0x06,0x45,0xDE};    //串口发送读取指令
    uint8_t Power_Reply_Fg;                                     //电源板反馈信息标识

    //检测信息
    uint8_t TakeOver_Enable;                                    //是否需要接管
    uint8_t YBlink_Enable;                                      //是否要硬黄闪
    uint8_t Error_YBlink_Enable;                                //异常是否硬黄闪
    uint8_t Opt_VCheck_Enable;                                  //灯控板是否需电压检测
    uint8_t Opt_ACheck_Enable;                                  //灯控板是否需电流检测

    //灯控板反馈信息
    struct Opt_Light_Reply_Structure  Opt_Reply_Buff[10];        //灯控板反馈点灯信息缓存,10块板子
    struct Opt_Light_Reply_ResultCount Opt_Reply_State[10];     //灯控板反馈点灯信息内容，10块板子
    
    //硬黄闪信息 ??
    uint16_t YBlink_Count1;                                     //处于硬黄闪计数
    uint16_t YBlink_Count2;                                     //非硬黄闪计数
    uint16_t YBlink_Count3;                                     //处于硬黄闪计数
    uint16_t YBlink_Count4;                                     //非硬黄闪计数
    uint8_t YBlink_Fg;                                          //

//函数声明
    
    void IWDG_Init(uint8_t pre,uint_fast16_t reload);
    void System_Clock_Init(uint32_t pll);
    void IWDG_Feed(void);
    void TIM2_Init(uint16_t arr,uint16_t psc);
    void GPIO_Init(void);
    void CAN1_Init(void);
    void Power_CAN_Send(uint16_t sid,uint8_t data[8]);
    void UART2_Init(uint32_t baudrate);
    void JSY_DataRequest(void);
    void Seek_Pointer(void);
    void Power_Reply(void);
    void Light_Opt(uint8_t n);
    void Check_Opt_Reply(void);
#endif
