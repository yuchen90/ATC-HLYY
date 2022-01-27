//声明需要使用的全局变量
#ifndef __MAIN_H__
#define __MAIN_H__

#include "stm32f1xx_hal.h"
#include "sys.h"
// #include "delay.h"

    #define VERSION 1
//灯控板工作指示灯显示
    #define MCU_RUN PAout(9)

//灯控板地址对应管脚 (与PCB管脚定义相反)
    #define ADDR0 PBin(6)
    #define ADDR1 PBin(7)
    #define ADDR2 PBin(8)
    #define ADDR3 PBin(9)

//点灯状态与引脚定义
    //灯组1对应bit-band地址
    #define R1 PCout(13)
    #define Y1 PCout(15)
    #define G1 PCout(1)
    //灯组2对应bit-band地址
    #define R2 PCout(3)
    #define Y2 PAout(3)
    #define G2 PAout(5)
    //灯组3对应bit-band地址
    #define R3 PAout(7)
    #define Y3 PCout(5)
    #define G3 PBout(1)
    //灯组4对应bit-band地址
    #define R4 PBout(11)
    #define Y4 PBout(13)
    #define G4 PBout(15)
    //灯色状态定义
    typedef enum
    {
        LED_OFF = 0u,
        LED_ON  = 1u
    }LED_STATE;

// CAN相关定义
    // CAN端口定义
    #define CANx_TX_PIN                    GPIO_PIN_12
    #define CANx_TX_GPIO_PORT              GPIOA
    #define CANx_RX_PIN                    GPIO_PIN_11
    #define CANx_RX_GPIO_PORT              GPIOA
    //CAN收，发指示灯
    #define CAN_Tx_LED PAout(0)
    #define CAN_Rx_LED PAout(1)
    // CAN时钟参数
    #define CANx                           CAN1
    #define CANx_CLK_ENABLE()              __HAL_RCC_CAN1_CLK_ENABLE()       //msp init
    #define CANx_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOA_CLK_ENABLE()

    #define CANx_FORCE_RESET()             __HAL_RCC_CAN1_FORCE_RESET()     //msp deinit
    #define CANx_RELEASE_RESET()           __HAL_RCC_CAN1_RELEASE_RESET()
    // CAN中断
    #define CANx_RX_IRQn                   USB_LP_CAN1_RX0_IRQn
    #define CANx_RX_IRQHandler             USB_LP_CAN1_RX0_IRQHandler

// TIM相关定义
    //TIM 时钟参数
    #define TIMx    TIM2
    #define TIMx_CLK_ENABLE()              __HAL_RCC_TIM2_CLK_ENABLE()
    //TIM 中断参数
    #define TIMx_IRQn                      TIM2_IRQn
    #define TIMx_IRQHandler                TIM2_IRQHandler

//电流与电压读取引脚bit-band定义
    // 灯组1
    #define R1_Volatge_State PCin(7)
    #define R1_Current_State PCin(14)
    #define Y1_Volatge_State PCin(8)
    #define Y1_Current_State PCin(0)
    #define G1_Volatge_State PCin(9)
    #define G1_Current_State PCin(2)
    // 灯组2
    #define R2_Volatge_State PAin(8)
    #define R2_Current_State PAin(2)
    #define Y2_Volatge_State PAin(15)
    #define Y2_Current_State PAin(4)
    #define G2_Volatge_State PCin(10)
    #define G2_Current_State PAin(6)
    // 灯组3
    #define R3_Volatge_State PCin(11)
    #define R3_Current_State PCin(4)
    #define Y3_Volatge_State PCin(12)
    #define Y3_Current_State PBin(0)
    #define G3_Volatge_State PDin(2)
    #define G3_Current_State PBin(10)
    // 灯组4
    #define R4_Volatge_State PBin(3)
    #define R4_Current_State PBin(12)
    #define Y4_Volatge_State PBin(4)
    #define Y4_Current_State PBin(14)
    #define G4_Volatge_State PBin(5)
    #define G4_Current_State PCin(6)
    
    //点灯占比值
    #define Voltage_Count 200u  //检查400次，电压至少累加到200次
    #define Current_Count 340u  //检查400次，电流至少累加到340次

#endif
