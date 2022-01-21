//������Ҫʹ�õ�ȫ�ֱ���
#ifndef __MAIN_H__
#define __MAIN_H__

#include "stm32f1xx_hal.h"
#include "sys.h"
// #include "delay.h"

//�ƿذ幤��ָʾ����ʾ
    #define MCU_RUN PAout(9)

//�ƿذ��ַ��Ӧ�ܽ� (��PCB�ܽŶ����෴)
    #define ADDR0 PBin(6)
    #define ADDR1 PBin(7)
    #define ADDR2 PBin(8)
    #define ADDR3 PBin(9)

//���״̬�����Ŷ���
    //����1��Ӧbit-band��ַ
    #define R1 PCout(13)
    #define Y1 PCout(15)
    #define G1 PCout(1)
    //����2��Ӧbit-band��ַ
    #define R2 PCout(3)
    #define Y2 PAout(3)
    #define G2 PAout(5)
    //����3��Ӧbit-band��ַ
    #define R3 PAout(7)
    #define Y3 PCout(5)
    #define G3 PBout(1)
    //����4��Ӧbit-band��ַ
    #define R4 PBout(11)
    #define Y4 PBout(13)
    #define G4 PBout(15)
    //��ɫ״̬����
    typedef enum
    {
        LED_OFF = 0u,
        LED_ON  = 1u
    }LED_STATE;

// CAN��ض���
    // CAN�˿ڶ���
    #define CANx_TX_PIN                    GPIO_PIN_12
    #define CANx_TX_GPIO_PORT              GPIOA
    #define CANx_RX_PIN                    GPIO_PIN_11
    #define CANx_RX_GPIO_PORT              GPIOA
    //CAN�գ���ָʾ��
    #define CAN_Tx_LED PAout(0)
    #define CAN_Rx_LED PAout(1)
    // CANʱ�Ӳ���
    #define CANx                           CAN1
    #define CANx_CLK_ENABLE()              __HAL_RCC_CAN1_CLK_ENABLE()       //msp init
    #define CANx_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOA_CLK_ENABLE()

    #define CANx_FORCE_RESET()             __HAL_RCC_CAN1_FORCE_RESET()     //msp deinit
    #define CANx_RELEASE_RESET()           __HAL_RCC_CAN1_RELEASE_RESET()
    // CAN�ж�
    #define CANx_RX_IRQn                   USB_LP_CAN1_RX0_IRQn
    #define CANx_RX_IRQHandler             USB_LP_CAN1_RX0_IRQHandler

// TIM��ض���
    //TIM ʱ�Ӳ���
    #define TIMx    TIM2
    #define TIMx_CLK_ENABLE()              __HAL_RCC_TIM2_CLK_ENABLE()
    //TIM �жϲ���
    #define TIMx_IRQn                      TIM2_IRQn
    #define TIMx_IRQHandler                TIM2_IRQHandler

//�������ѹ��ȡ����bit-band����
    // ����1
    #define Voltage_R1_Count PCin(7)
    #define Current_R1_Count PCin(14)
    #define Voltage_Y1_Count PCin(8)
    #define Current_Y1_Count PCin(0)
    #define Voltage_G1_Count PCin(9)
    #define Current_G1_Count PCin(2)
    // ����2
    #define Voltage_R2_Count PAin(8)
    #define Current_R2_Count PAin(2)
    #define Voltage_Y2_Count PAin(15)
    #define Current_Y2_Count PAin(4)
    #define Voltage_G2_Count PCin(10)
    #define Current_G2_Count PAin(6)
    // ����3
    #define Voltage_R3_Count PCin(11)
    #define Current_R3_Count PCin(4)
    #define Voltage_Y3_Count PCin(12)
    #define Current_Y3_Count PBin(0)
    #define Voltage_G3_Count PDin(2)
    #define Current_G3_Count PBin(10)
    // ����4
    #define Voltage_R4_Count PBin(3)
    #define Current_R4_Count PBin(12)
    #define Voltage_Y4_Count PBin(4)
    #define Current_Y4_Count PBin(14)
    #define Voltage_G4_Count PBin(5)
    #define Current_G4_Count PCin(6)

#endif
