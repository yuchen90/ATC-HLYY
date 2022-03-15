//声明需要使用的全局变量
#ifndef __MAIN_H__
#define __MAIN_H__
//main.h 宏定义与结构体声明 
#include "stm32f1xx_hal.h"
#include "sys.h"
//stm32f1xx_hal.h 引用，因为一些外设名字宏定义修改，方便移植
//sys.h 引用，stm32 位带操作

#define VERSION 1
#define ERROR_TIME 12

//GPIO 引脚使用
    //GPIO 输出
    #define MCU_RUN                        PBout(1)
    #define Y_FLASH_ENABLE                 PCout(6)     //50HZ50%信号输出，使黄闪板工作在正常模式
    //GPIO 输入
    #define Y_FLASH_FEEDBACK               PCin(10)     //黄闪版状态，上拉输入低有效。
    //GPIO 状态
    typedef enum
    {
        LED_OFF = 0u,
        LED_ON  = 1u
    }LED_STATE;

//一般状态定义
    typedef enum
    {
        OFF = 0u,
        ON  = 1u
    }STATE;

// CAN相关定义
    // CAN 使能开关
    #define CAN1_EN                        1u
    // CAN 端口定义
    #define CANx_TX_PIN                    GPIO_PIN_12
    #define CANx_TX_GPIO_PORT              GPIOA
    #define CANx_RX_PIN                    GPIO_PIN_11
    #define CANx_RX_GPIO_PORT              GPIOA
    //CAN收 发指示灯
    #define CAN_Tx_LED                     PBout(10)
    #define CAN_Rx_LED                     PBout(11)
    // CAN 时钟参数
    #define CANx                           CAN1
    #define CANx_CLK_ENABLE()              __HAL_RCC_CAN1_CLK_ENABLE()       //msp init
    #define CANx_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOA_CLK_ENABLE()
    // CAN中断
    #define CANx_RX_IRQn                   USB_LP_CAN1_RX0_IRQn

// TIM相关定义
    //TIM 时钟使能
    #define TIM2_EN                        1u
    //TIM 时钟参数
    #define TIMx                           TIM2
    #define TIMx_CLK_ENABLE()              __HAL_RCC_TIM2_CLK_ENABLE()
    //TIM 中断参数
    #define TIMx_IRQn                      TIM2_IRQn

// USART相关定义
    //USART 使能开关
    #define UART2_EN                      1u
    //USART 引脚参数
    #define UARTx_Tx_PIN                  GPIO_PIN_2
    #define UARTx_Tx_GPIO_PORT            GPIOA
    #define UARTx_Rx_PIN                  GPIO_PIN_3
    #define UARTx_Rx_GPIO_PORT            GPIOA
    //USART 外设参数
    #define UARTx                         USART2
    #define UARTx_CLK_ENABLE              __HAL_RCC_USART2_CLK_ENABLE()       //msp init
    #define UARTx_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOA_CLK_ENABLE()
    //USART 中断参数
    #define UARTx_IRQn                    USART2_IRQn
    //USART 接收参数
    #define UART_RxDataSize               17u

//结构体定义
	typedef struct TakeOver_Structure
	{
		u8 duration;        //点灯持续时间
		u8 cmd[15];         //点灯状态 共120bits 前60位   为0-4号灯控板，后60位为5-9号灯控板
	} TakeOverStructure;
	
	typedef struct Opt_Light_Reply_Structure
	{
		uint8_t ReplyState;          //灯控板是否反馈点灯信息 0：无  1：有
		uint8_t data[8];             //灯控板反馈的8字节点灯信息存储数组
		
		uint8_t LightColour[4];     //灯组（通道）当前灯色
		uint8_t LightState[4];      //灯组状态
		uint8_t RedVoltage[4];      //灯组红灯电压
		uint8_t RedCurrent[4];      //灯组红灯电流
		uint8_t YellowVoltage[4];   //灯组黄灯电压
		uint8_t YellowCurrent[4];   //灯组黄灯电流
		uint8_t GreenVoltage[4];    //灯组绿灯电压
		uint8_t GreenCurrent[4];    //灯组绿灯电流
		
	} Opt_Light_Reply_Structure;

    //////////////////
/* 信号故障检测逻辑
	1. 没有电绿灯   绿灯有电压
	2.   点亮绿灯   红灯有电压
	3.   点亮红灯   红灯无电流
	4      点黄灯   黄灯无电流
	
	连续12次
*/	
	typedef struct Opt_Light_Reply_ResultCount
	{
		uint8_t Check_Enable;		//是否需要检测
		uint8_t	NoReplyTimes;       //需要检查，但没有收到灯控板回复点灯状态的次数

		uint8_t	Red_Received_RV_times[4];       //点红灯时，有红灯电压计数
		uint8_t	Yellow_Received_YV_times[4];    //点黄灯时，有黄灯电压计数
		uint8_t	Green_Received_GV_times[4];     //点绿灯时，有绿灯电压计数

		uint8_t	Red_Received_RC_times[4];	    //点红灯时，有红灯电流计数	
		uint8_t	Yellow_Received_YC_times[4];    //点黄灯时，有黄灯电流计数		
		uint8_t	Green_Received_GC_times[4];     //点绿灯时，有绿灯电流计数
				
        uint8_t	Received_RV_times[4];		    //非红灯时，有红灯电压计数
		uint8_t	Received_YV_times[4];		    //非黄灯时，有黄灯电压计数		
		uint8_t	Received_GV_times[4];		    //非绿灯时，有绿灯电压计数
		
		uint8_t	Received_RC_times[4];		    //非红灯时，有红灯电流计数		
		uint8_t	Received_YC_times[4];		    //非黄灯时，有黄灯电流计数		
		uint8_t	Received_GC_times[4];		    //非绿灯时，有绿灯电流计数
		
	} Opt_Light_Reply_ResultCount;
	
#endif
