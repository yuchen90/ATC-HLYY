//声明需要使用的全局变量
#ifndef __MAIN_H__
#define __MAIN_H__

#include "stm32f1xx_hal.h"
#include "sys.h"

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

///////////////////////////////////////////////////////////////////////////////////////////////////////
#define VERSION    1u
    
//灯控板工作指示灯显示
    #define MCU_RUN    PAout(9)

//灯控板地址对应管脚 (与PCB管脚定义相反)
    #define ADDR0    PBin(6)
    #define ADDR1    PBin(7)
    #define ADDR2    PBin(8)
    #define ADDR3    PBin(9)

//点灯状态与引脚定义
    //灯组1对应bit-band地址
    #define R1    PCout(13)
    #define Y1    PCout(15)
    #define G1    PCout(1)
    //灯组2对应bit-band地址
    #define R2    PCout(3)
    #define Y2    PAout(3)
    #define G2    PAout(5)
    //灯组3对应bit-band地址
    #define R3    PAout(7)
    #define Y3    PCout(5)
    #define G3    PBout(1)
    //灯组4对应bit-band地址
    #define R4    PBout(11)
    #define Y4    PBout(13)
    #define G4    PBout(15)
    //灯色状态定义
    typedef enum
    {
        LED_OFF=0u,
        LED_ON=1u
    }LED_STATE;

// CAN相关定义
    // CAN端口定义
    #define CAN1_Tx_PIN                    GPIO_PIN_12
    #define CAN1_Tx_GPIO_PORT              GPIOA
    #define CAN1_Rx_PIN                    GPIO_PIN_11
    #define CAN1_Rx_GPIO_PORT              GPIOA
    //CAN收，发指示灯
    #define CAN_Tx_LED                     PAout(0)
    #define CAN_Rx_LED                     PAout(1)
    // CAN时钟参数
    #define CAN1_CLK_ENABLE()              __HAL_RCC_CAN1_CLK_ENABLE()          //msp init
    #define CAN1_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOA_CLK_ENABLE()

    #define CAN1_FORCE_RESET()             __HAL_RCC_CAN1_FORCE_RESET()         //msp deinit
    #define CAN1_RELEASE_RESET()           __HAL_RCC_CAN1_RELEASE_RESET()
    // CAN中断
    #define CAN1_Rx_IRQn                   USB_LP_CAN1_RX0_IRQn

// TIM相关定义
    //TIM 时钟参数
    #define TIM2_CLK_ENABLE()              __HAL_RCC_TIM2_CLK_ENABLE()          //msp init
    //TIM 中断参数
    #define TIM2_FORCE_RESET()             __HAL_RCC_TIM2_FORCE_RESET()         //msp deinit
    #define TIM2_RELEASE_RESET()           __HAL_RCC_TIM2_RELEASE_RESET()

//电流与电压读取引脚bit-band定义
    // 灯组1
    #define R1_Volatge_State    PCin(7)
    #define R1_Current_State    PCin(14)
    #define Y1_Volatge_State    PCin(8)
    #define Y1_Current_State    PCin(0)
    #define G1_Volatge_State    PCin(9)
    #define G1_Current_State    PCin(2)
    // 灯组2
    #define R2_Volatge_State    PAin(8)
    #define R2_Current_State    PAin(2)
    #define Y2_Volatge_State    PAin(15)
    #define Y2_Current_State    PAin(4)
    #define G2_Volatge_State    PCin(10)
    #define G2_Current_State    PAin(6)
    // 灯组3
    #define R3_Volatge_State    PCin(11)
    #define R3_Current_State    PCin(4)
    #define Y3_Volatge_State    PCin(12)
    #define Y3_Current_State    PBin(0)
    #define G3_Volatge_State    PDin(2)
    #define G3_Current_State    PBin(10)
    // 灯组4
    #define R4_Volatge_State    PBin(3)
    #define R4_Current_State    PBin(12)
    #define Y4_Volatge_State    PBin(4)
    #define Y4_Current_State    PBin(14)
    #define G4_Volatge_State    PBin(5)
    #define G4_Current_State    PCin(6)
    
    //点灯占比值
    #define Voltage_Count_Std 100u  //需测试，再决定具体数值
    #define Current_Count_Std 170u  //需测试，再决定具体数值

#endif
