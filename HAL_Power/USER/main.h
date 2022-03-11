//������Ҫʹ�õ�ȫ�ֱ���
#ifndef __MAIN_H__
#define __MAIN_H__
//main.h �궨����ṹ������ 
#include "stm32f1xx_hal.h"
#include "sys.h"
//stm32f1xx_hal.h ���ã���ΪһЩ�������ֺ궨���޸ģ�������ֲ
//sys.h ���ã�stm32 λ������

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
    #define CANx_TX_PIN                    GPIO_PIN_12
    #define CANx_TX_GPIO_PORT              GPIOA
    #define CANx_RX_PIN                    GPIO_PIN_11
    #define CANx_RX_GPIO_PORT              GPIOA
    //CAN�� ��ָʾ��
    #define CAN_Tx_LED                     PBout(10)
    #define CAN_Rx_LED                     PBout(11)
    // CAN ʱ�Ӳ���
    #define CANx                           CAN1
    #define CANx_CLK_ENABLE()              __HAL_RCC_CAN1_CLK_ENABLE()       //msp init
    #define CANx_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOA_CLK_ENABLE()
    // CAN�ж�
    #define CANx_RX_IRQn                   USB_LP_CAN1_RX0_IRQn

// TIM��ض���
    //TIM ʱ��ʹ��
    #define TIM2_EN                        1u
    //TIM ʱ�Ӳ���
    #define TIMx                           TIM2
    #define TIMx_CLK_ENABLE()              __HAL_RCC_TIM2_CLK_ENABLE()
    //TIM �жϲ���
    #define TIMx_IRQn                      TIM2_IRQn

// USART��ض���
    //USART ʹ�ܿ���
    #define UART2_EN                      1u
    //USART ���Ų���
    #define UARTx_Tx_PIN                  GPIO_PIN_2
    #define UARTx_Tx_GPIO_PORT            GPIOA
    #define UARTx_Rx_PIN                  GPIO_PIN_3
    #define UARTx_Rx_GPIO_PORT            GPIOA
    //USART �������
    #define UARTx                         USART2
    #define UARTx_CLK_ENABLE              __HAL_RCC_USART2_CLK_ENABLE()       //msp init
    #define UARTx_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOA_CLK_ENABLE()
    //USART �жϲ���
    #define UARTx_IRQn                    USART2_IRQn
    //USART ���ղ���
    #define UART_RxDataSize               1u

//�ṹ�嶨��
	typedef struct TakeOver_Structure
	{
		u8 duration;        //��Ƴ���ʱ��
		u8 cmd[15];         //���״̬ ��120bits ǰ60λ   Ϊ0-4�ŵƿذ壬��60λΪ5-9�ŵƿذ�
	} TakeOverStructure;
	
	typedef struct Opt_Light_Reply_Structure
	{
		uint8_t ReplyState;          //�ƿذ��Ƿ��������Ϣ 0����  1����
		uint8_t data[8];             //�ƿذ巴����8�ֽڵ����Ϣ�洢����
		
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
		uint8_t	NoReplyTimes;       //��Ҫ��飬��û���յ��ƿذ�ظ����״̬�Ĵ���

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
