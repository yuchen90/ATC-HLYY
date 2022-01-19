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

// CAN�˿ڶ���
    #define CANx_TX_PIN                    GPIO_PIN_12
    #define CANx_TX_GPIO_PORT              GPIOA
    #define CANx_RX_PIN                    GPIO_PIN_11
    #define CANx_RX_GPIO_PORT              GPIOA
    //CAN�գ���ָʾ��
    #define CAN_Tx_LED PAout(0)
    #define CAN_Rx_LED PAout(1)

#endif
