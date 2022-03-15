#ifndef __GLOBAL_VARIABLE_H__
#define __GLOBAL_VARIABLE_H__
//ȫ�ֱ��� �� ���� ����
#include "stdint.h"
//uint_tX ����ͷ�ļ�

//ϵͳ����
    uint32_t SYSTEM_Time_Fg;                                    //TIM2�жϣ�100usһ�Σ�++�� TFg(TimeFlag ��д)
    uint32_t SYSTEM_Time_Fg1;                                   //�ƿذ���˸��������ʱ����0.
    uint32_t CAN_DataRead_Fg;                                   //���ذ巢���ƿذ巢�͵�����ݣ���Դ����յ��ı�ʶ��

// CAN��Ϣbuff
    //һ����Ϣ
    uint8_t CAN_Id_CANType;                                     //ͨ��CAN��ID������Э�鶨���CAN����
    uint8_t CAN_FrameNumber;                                    //��׼֡�����ذ巢�͸��ƿذ������� �ڼ�����    ��չ֡���ӹ���Ϣ ֡���
    
    //�ƿذ�����Ϣ
    uint8_t CAN_Buff[16];                                       //�������ذ巢���ƿذ������ݽ��ջ���
    uint8_t cmd[15];                                            //�ӹ���Ϣ ���ָ��
    uint8_t Blink_Id_Now;                                       //�����Ϣ����˸���Ƿ������ʶ�� 0���� 1����
    uint8_t Blink_Id_Before;                                    //��һ����˸��ʶ
    uint8_t Opt_CheckReply_Buff;                                //�ƿذ��Ʒ�����ʶ������
    uint8_t Opt_CheckReply_1st;                                 //��һ�����ݵƿذ��Ʒ�����ʶ
    uint8_t Opt_CheckReply_2nd;                                 //�ڶ������ݵƿذ��Ʒ�����ʶ
    uint8_t Opt_BoardId;                                        //�ƿذ���
    
    //��Դ��
    uint8_t Power_Reply_Fg;                                     //��Դ�巴����Ϣ��ʶ
    
    //�ӹ���Ϣ
    uint32_t CheckSum;                                          //�ӹ���Ϣ��4�ֽ�У��ֵ
    uint16_t ArrayNum;                                          //�ӹ���Ϣ �ӹ����ݸ���
    uint16_t FrameNum;                                          //�ӹ���Ϣ ֮����յ�֡����
   
    struct TakeOver_Structure TakeOver_Structure_Use[160];      //�ӹ���Ϣ ����ʹ����Ϣ
    struct TakeOver_Structure TakeOver_Structure_Buff[160];     //�ӹ���Ϣ ��Ϣ���ջ���
    uint16_t TakeOver_Pointer;                                  //�ӹ���Ϣ����ָ��
    uint16_t TakeOver_DataNum;                                  //�ӹ���Ϣ���ݸ������ܽ�������  ���� ArrayNum
    uint8_t RunTime;                                            //��Դ��ӹ�ʱ����ǰ���ĵĵ�Ƴ���ʱ��

    //�е���
    uint8_t JSY_MK163_ReadBuff[20];                             //�е��Ӧ��ȡ���ݻ���
    uint8_t JSY_MK163_ReadNum;                                  //�е��Ӧ��ȡ���� Ԫ������
    uint16_t JSY_MK163_ReadRequest_Fg;                          //�е��Ӧ��Ϣ��ѯ������ʶ�� ÿ���ѯ1�Σ�ÿ�ν������������Ϣ֡��1�����ڵ���4ʱ����0
    uint8_t SendBuff[8] = {0x01,0x03,0x00,0x48,0x00,0x06,0x45,0xDE};    //���ڷ��Ͷ�ȡָ��

    //�����Ϣ
    uint8_t TakeOver_Enable;                                    //�Ƿ���Ҫ�ӹ�
    uint8_t YBlink_Enable;                                      //�Ƿ�ҪӲ����
    uint8_t Error_YBlink_Enable;                                //�쳣�Ƿ�Ӳ����
    uint8_t Opt_VCheck_Enable;                                  //�ƿذ��Ƿ����ѹ���
    uint8_t Opt_ACheck_Enable;                                  //�ƿذ��Ƿ���������

    //�ƿذ巴����Ϣ
    struct Opt_Light_Reply_Structure Opt_Reply_Buff[10];        //�ƿذ巴�������Ϣ����,10�����
    struct Opt_Light_Reply_ResultCount Opt_Reply_State[10];     //�ƿذ巴�������Ϣ���ݣ�10�����
    
    //Ӳ������Ϣ ??
    uint16_t YBlink_Count1;                                     //����Ӳ��������
    uint16_t YBlink_Count2;                                     //��Ӳ��������
    uint16_t YBlink_Count3;                                     //����Ӳ��������
    uint16_t YBlink_Count4;                                     //��Ӳ��������
    uint8_t YBlink_Fg;                                          //

//��������
    
    void IWDG_Init(uint8_t pre,uint_fast16_t reload);
    void IWDG_Feed(void);
    void TIM2_Init(uint16_t arr,uint16_t psc);
    void GPIO_Init(void);
    void UART_Init(uint32_t baudrate);
    void JSY_DataRequest(void);

    extern HAL_UART_StateTypeDef HAL_UART_GetRxState(UART_HandleTypeDef *huart);
    extern HAL_UART_StateTypeDef HAL_UART_GetgState(UART_HandleTypeDef *huart);

#endif
