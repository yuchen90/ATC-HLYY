//������Ҫʹ�õ�ȫ�ֱ���
#ifndef __MAIN_H__
#define __MAIN_H__

#include "stm32f1xx_hal.h"
#include "sys.h"

//λ������,ʵ��51���Ƶ�GPIO���ƹ���
//����ʵ��˼��,�ο�<<CM3Ȩ��ָ��>>������(87ҳ~92ҳ).
//IO�ڲ����궨��
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO�ڵ�ַӳ��
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
 
//IO�ڲ���,ֻ�Ե�һ��IO��!
//ȷ��n��ֵС��16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //��� 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //��� 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //��� 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����

///////////////////////////////////////////////////////////////////////////////////////////////////////
#define VERSION    1u
    
//�ƿذ幤��ָʾ����ʾ
    #define MCU_RUN    PAout(9)

//�ƿذ��ַ��Ӧ�ܽ� (��PCB�ܽŶ����෴)
    #define ADDR0    PBin(6)
    #define ADDR1    PBin(7)
    #define ADDR2    PBin(8)
    #define ADDR3    PBin(9)

//���״̬�����Ŷ���
    //����1��Ӧbit-band��ַ
    #define R1    PCout(13)
    #define Y1    PCout(15)
    #define G1    PCout(1)
    //����2��Ӧbit-band��ַ
    #define R2    PCout(3)
    #define Y2    PAout(3)
    #define G2    PAout(5)
    //����3��Ӧbit-band��ַ
    #define R3    PAout(7)
    #define Y3    PCout(5)
    #define G3    PBout(1)
    //����4��Ӧbit-band��ַ
    #define R4    PBout(11)
    #define Y4    PBout(13)
    #define G4    PBout(15)
    //��ɫ״̬����
    typedef enum
    {
        LED_OFF=0u,
        LED_ON=1u
    }LED_STATE;

// CAN��ض���
    // CAN�˿ڶ���
    #define CAN1_Tx_PIN                    GPIO_PIN_12
    #define CAN1_Tx_GPIO_PORT              GPIOA
    #define CAN1_Rx_PIN                    GPIO_PIN_11
    #define CAN1_Rx_GPIO_PORT              GPIOA
    //CAN�գ���ָʾ��
    #define CAN_Tx_LED                     PAout(0)
    #define CAN_Rx_LED                     PAout(1)
    // CANʱ�Ӳ���
    #define CAN1_CLK_ENABLE()              __HAL_RCC_CAN1_CLK_ENABLE()          //msp init
    #define CAN1_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOA_CLK_ENABLE()

    #define CAN1_FORCE_RESET()             __HAL_RCC_CAN1_FORCE_RESET()         //msp deinit
    #define CAN1_RELEASE_RESET()           __HAL_RCC_CAN1_RELEASE_RESET()
    // CAN�ж�
    #define CAN1_Rx_IRQn                   USB_LP_CAN1_RX0_IRQn

// TIM��ض���
    //TIM ʱ�Ӳ���
    #define TIM2_CLK_ENABLE()              __HAL_RCC_TIM2_CLK_ENABLE()          //msp init
    //TIM �жϲ���
    #define TIM2_FORCE_RESET()             __HAL_RCC_TIM2_FORCE_RESET()         //msp deinit
    #define TIM2_RELEASE_RESET()           __HAL_RCC_TIM2_RELEASE_RESET()

//�������ѹ��ȡ����bit-band����
    // ����1
    #define R1_Volatge_State    PCin(7)
    #define R1_Current_State    PCin(14)
    #define Y1_Volatge_State    PCin(8)
    #define Y1_Current_State    PCin(0)
    #define G1_Volatge_State    PCin(9)
    #define G1_Current_State    PCin(2)
    // ����2
    #define R2_Volatge_State    PAin(8)
    #define R2_Current_State    PAin(2)
    #define Y2_Volatge_State    PAin(15)
    #define Y2_Current_State    PAin(4)
    #define G2_Volatge_State    PCin(10)
    #define G2_Current_State    PAin(6)
    // ����3
    #define R3_Volatge_State    PCin(11)
    #define R3_Current_State    PCin(4)
    #define Y3_Volatge_State    PCin(12)
    #define Y3_Current_State    PBin(0)
    #define G3_Volatge_State    PDin(2)
    #define G3_Current_State    PBin(10)
    // ����4
    #define R4_Volatge_State    PBin(3)
    #define R4_Current_State    PBin(12)
    #define Y4_Volatge_State    PBin(4)
    #define Y4_Current_State    PBin(14)
    #define G4_Volatge_State    PBin(5)
    #define G4_Current_State    PCin(6)
    
    //���ռ��ֵ
    #define Voltage_Count_Std 100u  //����ԣ��پ���������ֵ
    #define Current_Count_Std 170u  //����ԣ��پ���������ֵ

#endif
