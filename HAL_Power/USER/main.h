//声明需要使用的全局变量
#ifndef __MAIN_H__
#define __MAIN_H__
//main.h 宏定义与结构体声明 
#include "stm32f1xx_hal.h"

//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
    #define CAN1_Tx_PIN                    GPIO_PIN_12
    #define CAN1_Tx_GPIO_PORT              GPIOA
    #define CAN1_Rx_PIN                    GPIO_PIN_11
    #define CAN1_Rx_GPIO_PORT              GPIOA
    //CAN收 发指示灯
    #define CAN_Tx_LED                     PBout(10)
    #define CAN_Rx_LED                     PBout(11)
    // CAN 时钟参数
    #define CAN1_CLK_ENABLE()              __HAL_RCC_CAN1_CLK_ENABLE()       //msp init
    #define CAN1_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOA_CLK_ENABLE()
    // CAN中断
    #define CAN1_Rx_SID_IRQn                   USB_LP_CAN1_RX0_IRQn
    #define CAN1_Rx_EXID_IRQn                  CAN1_RX1_IRQn 

// TIM相关定义
    //TIM 时钟使能
    #define TIM2_EN                        1u
    //TIM 时钟参数
    #define TIM2_CLK_ENABLE()              __HAL_RCC_TIM2_CLK_ENABLE()

// USART相关定义
    //USART 使能开关
    #define UART2_EN                      1u
    //USART 引脚参数
    #define UART2_Tx_PIN                  GPIO_PIN_2
    #define UART2_Tx_GPIO_PORT            GPIOA
    #define UART2_Rx_PIN                  GPIO_PIN_3
    #define UART2_Rx_GPIO_PORT            GPIOA
    //USART 外设参数
    #define UART2_CLK_ENABLE              __HAL_RCC_USART2_CLK_ENABLE()       //msp init
    #define UART2_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOA_CLK_ENABLE()
    #define UART2_DMA_CLK_ENABLE()        __HAL_RCC_DMA1_CLK_ENABLE()
    //USART 中断参数
    #define UART2_IRQn                    USART2_IRQn
    #define UART2_DMA_Tx_IRQn             DMA1_Channel7_IRQn
    #define UART2_DMA_Rx_IRQn             DMA1_Channel6_IRQn
    //USART 参数
    #define UART2_RxDataSize               17u
    #define UART2_TxDataSize               8u

//结构体定义
	typedef struct TakeOver_Structure
	{
		uint8_t Duration;        //点灯持续时间
		uint8_t Cmd[15];         //点灯状态 共120bits 前60位   为0-4号灯控板，后60位为5-9号灯控板
	} TakeOverStructure;
	
	typedef struct Opt_Light_Reply_Structure
	{
		uint8_t ReplyState;          //灯控板是否反馈点灯信息 0：无  1：有
		uint8_t Data[8];             //灯控板反馈的8字节点灯信息存储数组
		
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
		uint8_t	No_Of_Reply_Times;       //需要检查，但没有收到灯控板回复点灯状态的次数

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
