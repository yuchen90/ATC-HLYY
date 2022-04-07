#ifndef __DECLARARTION_H
#define __DECLARARTION_H
//extern ���� global_variable.h �����ĺ�����ȫ�ֱ���

#include "stdint.h"
#include "stm32f1xx_hal.h"

//������
    extern UART_HandleTypeDef POWER_UART2_Handle;
    extern uint8_t UART_Rx_Buff[UART2_RxDataSize];
    extern DMA_HandleTypeDef UART2Rx_DMA_Handle;
    extern DMA_HandleTypeDef UART2Tx_DMA_Handle;

    extern CAN_HandleTypeDef CAN_Handle;
    extern CAN_TxHeaderTypeDef CAN_TxHeader;
    extern CAN_RxHeaderTypeDef CAN_RxHeader;

    extern TIM_HandleTypeDef TIM2_Handle;
//ϵͳ����
    extern uint32_t System_Time_Fg;                                      //TIM2�жϣ�100usһ�Σ�++�� TFg(TimeFlag ��д)
    extern uint32_t System_Time_Fg1;                                     //�ƿذ���˸��������ʱ����0.
    extern uint32_t CAN_DataRead_Fg;                                    //���ذ巢���ƿذ巢�͵�����ݣ���Դ����յ��ı�ʶ��

// CAN��Ϣbuff
    //һ����Ϣ
    extern uint8_t CAN_Id_CANType;                                      //ͨ��CAN��ID������Э�鶨���CAN����
    extern uint8_t CAN_FrameNumber;                                     //��׼֡�����ذ巢�͸��ƿذ������� �ڼ�����    ��չ֡���ӹ���Ϣ ֡���
    
    //�ƿذ�����Ϣ
    extern uint8_t CAN_Buff[16];                                        //�������ذ巢���ƿذ������ݽ��ջ���
    extern uint8_t CMD[15];                                             //�ӹ���Ϣ ���ָ��
    extern uint8_t Blink_Id;                                            //�����Ϣ����˸���Ƿ������ʶ�� 0���� 1����
    extern uint8_t Blink_Id_Before;                                     //��һ����˸��ʶ
    extern uint8_t Opt_CheckReply_Fg;                                   //�ƿذ��Ʒ�����ʶ������
    extern uint8_t Opt_CheckReply_1st;                                  //��һ�����ݵƿذ��Ʒ�����ʶ
    extern uint8_t Opt_CheckReply_2nd;                                  //�ڶ������ݵƿذ��Ʒ�����ʶ
    extern uint8_t Opt_BoardId;                                         //�ƿذ���
    
    //��Դ��
    extern uint8_t Power_Reply_Fg;                                      //��Դ�巴����Ϣ��ʶ
    
    //�ӹ���Ϣ
    extern uint32_t CheckSum;                                           //�ӹ���Ϣ��4�ֽ�У��ֵ
    extern uint16_t ArrayNum;                                           //�ӹ���Ϣ �ӹ����ݸ���
    extern uint16_t FrameNum;                                           //�ӹ���Ϣ ֮����յ�֡����
   
    extern struct TakeOver_Structure TakeOver_Structure_Use[160];       //�ӹ���Ϣ ����ʹ����Ϣ
    extern struct TakeOver_Structure TakeOver_Structure_Buff[160];      //�ӹ���Ϣ ��Ϣ���ջ���
    extern uint16_t TakeOver_Pointer;                                   //�ӹ���Ϣ����ָ��
    extern uint16_t TakeOver_DataNum;                                   //�ӹ���Ϣ���ݸ������ܽ�������  ���� ArrayNum
    extern uint8_t RunTime;                                             //��Դ��ӹ�ʱ����ǰ���ĵĵ�Ƴ���ʱ��

    //�е���
    extern uint8_t JSY_MK163_ReadBuff[20];                              //�е��Ӧ��ȡ���ݻ���
    extern uint8_t JSY_MK163_ReadNum;                                   //�е��Ӧ��ȡ���� Ԫ������
    extern uint16_t JSY_MK163_ReadRequest_Fg;                           //�е��Ӧ��Ϣ��ѯ������ʶ�� ÿ���ѯ1�Σ�ÿ�ν������������Ϣ֡��1�����ڵ���4ʱ����0
    extern uint8_t UART_Send_Buff[UART2_TxDataSize];

    //�����Ϣ(���ذ�->��Դ��)
    extern uint8_t TakeOver_Enable;                                     //�Ƿ���Ҫ�ӹ�
    extern uint8_t YBlink_Enable;                                       //�Ƿ�ҪӲ����
    extern uint8_t Error_YBlink_Enable;                                 //�쳣�Ƿ�Ӳ����
    extern uint8_t Opt_VCheck_Enable;                                   //�ƿذ��Ƿ����ѹ���
    extern uint8_t Opt_ACheck_Enable;                                   //�ƿذ��Ƿ���������
    
    //�ƿذ巴����Ϣ
    extern struct Opt_Light_Reply_Structure Opt_Reply_Buff[10];         //�ƿذ巴�������Ϣ����,10�����
    extern struct Opt_Light_Reply_ResultCount Opt_Reply_State[10];      //�ƿذ巴�������Ϣ���ݣ�10�����
    
//Ӳ������Ϣ ??
    extern uint16_t YBlink_Count1;                                      //����Ӳ��������
    extern uint16_t YBlink_Count2;                                      //��Ӳ��������
    extern uint16_t YBlink_Count3;                                      //����Ӳ��������
    extern uint16_t YBlink_Count4;                                      //��Ӳ��������
    extern uint8_t YBlink_Fg;                                           //

//DEBUG ����
    extern uint32_t w,e,t,r;
#endif
