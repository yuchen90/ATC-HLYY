//声明需要使用的全局变量
#ifndef __MAIN_H__
#define __MAIN_H__

#include "stm32f1xx_hal.h"
#include "sys.h"
// #include "delay.h"

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

// CAN端口定义
    #define CANx_TX_PIN                    GPIO_PIN_12
    #define CANx_TX_GPIO_PORT              GPIOA
    #define CANx_RX_PIN                    GPIO_PIN_11
    #define CANx_RX_GPIO_PORT              GPIOA
    //CAN收，发指示灯
    #define CAN_Tx_LED PAout(0)
    #define CAN_Rx_LED PAout(1)

#endif
