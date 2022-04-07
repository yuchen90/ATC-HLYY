//������Ҫʹ�õ�ȫ�ֱ���
#ifndef __MAIN_H__
#define __MAIN_H__
//main.h �궨����ṹ������ 
#include "stm32f1xx_hal.h"

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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define VERSION 1
#define ERROR_TIME 12

//GPIO ����ʹ��
    //GPIO ���
    #define MCU_RUN                        PBout(1)
    #define Y_FLASH_ENABLE                 PCout(6)     //50HZ50%�ź������ʹ�����幤��������ģʽ
    //GPIO ����
    #define Y_FLASH_FEEDBACK               PCin(10)     //������״̬�������������Ч��
    //GPIO ״̬
    typedef enum
    {
        LED_OFF = 0u,
        LED_ON  = 1u
    }LED_STATE;

//һ��״̬����
    typedef enum
    {
        OFF = 0u,
        ON  = 1u
    }STATE;

// CAN��ض���
    // CAN ʹ�ܿ���
    #define CAN1_EN                        1u
    // CAN �˿ڶ���
    #define CAN1_Tx_PIN                    GPIO_PIN_12
    #define CAN1_Tx_GPIO_PORT              GPIOA
    #define CAN1_Rx_PIN                    GPIO_PIN_11
    #define CAN1_Rx_GPIO_PORT              GPIOA
    //CAN�� ��ָʾ��
    #define CAN_Tx_LED                     PBout(10)
    #define CAN_Rx_LED                     PBout(11)
    // CAN ʱ�Ӳ���
    #define CAN1_CLK_ENABLE()              __HAL_RCC_CAN1_CLK_ENABLE()       //msp init
    #define CAN1_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOA_CLK_ENABLE()
    // CAN�ж�
    #define CAN1_Rx_SID_IRQn                   USB_LP_CAN1_RX0_IRQn
    #define CAN1_Rx_EXID_IRQn                  CAN1_RX1_IRQn 

// TIM��ض���
    //TIM ʱ��ʹ��
    #define TIM2_EN                        1u
    //TIM ʱ�Ӳ���
    #define TIM2_CLK_ENABLE()              __HAL_RCC_TIM2_CLK_ENABLE()

// USART��ض���
    //USART ʹ�ܿ���
    #define UART2_EN                      1u
    //USART ���Ų���
    #define UART2_Tx_PIN                  GPIO_PIN_2
    #define UART2_Tx_GPIO_PORT            GPIOA
    #define UART2_Rx_PIN                  GPIO_PIN_3
    #define UART2_Rx_GPIO_PORT            GPIOA
    //USART �������
    #define UART2_CLK_ENABLE              __HAL_RCC_USART2_CLK_ENABLE()       //msp init
    #define UART2_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOA_CLK_ENABLE()
    #define UART2_DMA_CLK_ENABLE()        __HAL_RCC_DMA1_CLK_ENABLE()
    //USART �жϲ���
    #define UART2_IRQn                    USART2_IRQn
    #define UART2_DMA_Tx_IRQn             DMA1_Channel7_IRQn
    #define UART2_DMA_Rx_IRQn             DMA1_Channel6_IRQn
    //USART ����
    #define UART2_RxDataSize               17u
    #define UART2_TxDataSize               8u

//�ṹ�嶨��
	typedef struct TakeOver_Structure
	{
		uint8_t Duration;        //��Ƴ���ʱ��
		uint8_t Cmd[15];         //���״̬ ��120bits ǰ60λ   Ϊ0-4�ŵƿذ壬��60λΪ5-9�ŵƿذ�
	} TakeOverStructure;
	
	typedef struct Opt_Light_Reply_Structure
	{
		uint8_t ReplyState;          //�ƿذ��Ƿ��������Ϣ 0����  1����
		uint8_t Data[8];             //�ƿذ巴����8�ֽڵ����Ϣ�洢����
		
		uint8_t LightColour[4];     //���飨ͨ������ǰ��ɫ
		uint8_t LightState[4];      //����״̬
		uint8_t RedVoltage[4];      //�����Ƶ�ѹ
		uint8_t RedCurrent[4];      //�����Ƶ���
		uint8_t YellowVoltage[4];   //����ƵƵ�ѹ
		uint8_t YellowCurrent[4];   //����ƵƵ���
		uint8_t GreenVoltage[4];    //�����̵Ƶ�ѹ
		uint8_t GreenCurrent[4];    //�����̵Ƶ���
		
	} Opt_Light_Reply_Structure;

    //////////////////
/* �źŹ��ϼ���߼�
	1. û�е��̵�   �̵��е�ѹ
	2.   �����̵�   ����е�ѹ
	3.   �������   ����޵���
	4      ��Ƶ�   �Ƶ��޵���
	
	����12��
*/	
	typedef struct Opt_Light_Reply_ResultCount
	{
		uint8_t Check_Enable;		//�Ƿ���Ҫ���
		uint8_t	No_Of_Reply_Times;       //��Ҫ��飬��û���յ��ƿذ�ظ����״̬�Ĵ���

		uint8_t	Red_Received_RV_times[4];       //����ʱ���к�Ƶ�ѹ����
		uint8_t	Yellow_Received_YV_times[4];    //��Ƶ�ʱ���лƵƵ�ѹ����
		uint8_t	Green_Received_GV_times[4];     //���̵�ʱ�����̵Ƶ�ѹ����

		uint8_t	Red_Received_RC_times[4];	    //����ʱ���к�Ƶ�������	
		uint8_t	Yellow_Received_YC_times[4];    //��Ƶ�ʱ���лƵƵ�������		
		uint8_t	Green_Received_GC_times[4];     //���̵�ʱ�����̵Ƶ�������
				
        uint8_t	Received_RV_times[4];		    //�Ǻ��ʱ���к�Ƶ�ѹ����
		uint8_t	Received_YV_times[4];		    //�ǻƵ�ʱ���лƵƵ�ѹ����		
		uint8_t	Received_GV_times[4];		    //���̵�ʱ�����̵Ƶ�ѹ����
		
		uint8_t	Received_RC_times[4];		    //�Ǻ��ʱ���к�Ƶ�������		
		uint8_t	Received_YC_times[4];		    //�ǻƵ�ʱ���лƵƵ�������		
		uint8_t	Received_GC_times[4];		    //���̵�ʱ�����̵Ƶ�������
		
	} Opt_Light_Reply_ResultCount;
	
#endif
