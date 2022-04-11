#ifndef __GLOBAL_VARIABLE_H__
#define __GLOBAL_VARIABLE_H__
//ȫ�ֱ��� �� ���� ����
#include "stdint.h"
#include "stm32f1xx_hal.h"

//������
    UART_HandleTypeDef POWER_UART2_Handle;
    uint8_t UART_Rx_Buff[UART2_RxDataSize];
    DMA_HandleTypeDef UART2Rx_DMA_Handle;
    DMA_HandleTypeDef UART2Tx_DMA_Handle;

    CAN_HandleTypeDef CAN_Handle;
    CAN_TxHeaderTypeDef CAN_TxHeader;
    CAN_RxHeaderTypeDef CAN_RxHeader;
    CAN_RxHeaderTypeDef CAN_RxHeader1;

    TIM_HandleTypeDef TIM2_Handle;

    IWDG_HandleTypeDef IWDG_Handle;

//ϵͳ����
    uint32_t System_Time_Fg;                                    //TIM2�жϣ�100usһ�Σ�++�� TFg(TimeFlag ��д)
    uint32_t System_Time_Fg1;                                   //�ƿذ���˸��������ʱ����0.
    uint32_t CAN_DataRead_Fg;                                   //���ذ巢���ƿذ巢�͵�����ݣ���Դ����յ��ı�ʶ��

// CAN��Ϣbuff
    //һ����Ϣ
    uint8_t CAN_Id_CANType;                                     //ͨ��CAN��ID������Э�鶨���CAN����
    uint8_t CAN_FrameNumber;                                    //��׼֡�����ذ巢�͸��ƿذ������� �ڼ�����    ��չ֡���ӹ���Ϣ ֡���
    
    //�ƿذ�����Ϣ
    uint8_t CAN_Buff[16];                                       //�������ذ巢���ƿذ������ݽ��ջ���
    uint8_t CMD[15];                                            //�ӹ���Ϣ ���ָ��
    uint8_t Blink_Id;                                           //�����Ϣ����˸���Ƿ������ʶ�� 0���� 1����
    uint8_t Blink_Id_Before;                                    //��һ����˸��ʶ
    uint8_t Opt_CheckReply_Fg;                                  //�ƿذ��Ʒ�����ʶ������
    uint8_t Opt_CheckReplyState_1st;                            //��һ�����ݵƿذ��Ʒ�����ʶ������ÿ��ƿذ屣��һ�Σ�������Ҫ��Ʒ���������ͨ����Ҫ��������ʹ����ƣ�
    uint8_t Opt_CheckReplyState_2nd;                            //�ڶ������ݵƿذ��Ʒ�����ʶ
    uint8_t Opt_BoardId;                                        //�ƿذ���
        
    //�ӹ���Ϣ
    uint32_t CheckSum;                                          //�ӹ���Ϣ��4�ֽ�У��ֵ
    uint16_t ArrayNum;                                          //�ӹ���Ϣ �ӹ����ݸ���������֮һ FrameNum
    uint16_t FrameNum;                                          //�ӹ���Ϣ ֮����յ�֡����
   
    struct TakeOver_Structure TakeOver_Structure_Use[160];      //�ӹ���Ϣ ����ʹ����Ϣ
    struct TakeOver_Structure TakeOver_Structure_Buff[160];     //�ӹ���Ϣ ��Ϣ���ջ���
    uint16_t TakeOver_Pointer;                                  //�ӹ���Ϣ����ָ��
    uint16_t TakeOver_DataNum;                                  //�ӹ���Ϣ���ݸ������ܽ�������  ���� ArrayNum
    uint8_t RunTime;                                            //��Դ��ӹ�ʱ����ǰ���ĵĵ�Ƴ���ʱ��

    //�е���
    uint8_t JSY_MK163_ReadBuff[20];                             //�е��Ӧ��ȡ���ݻ���
    uint8_t JSY_MK163_ReadNum;                                  //�е��Ӧ��ȡ���� Ԫ������
    uint16_t JSY_MK163_ReadRequest_Fg;                          //�е��Ӧ��Ϣ��ѯ������ʶ�� ÿ���ѯ4�Σ�ÿ�ν������������Ϣ֡��1�����ڵ���4ʱ����0
    uint8_t UART_Send_Buff[UART2_TxDataSize] = {0x01,0x03,0x00,0x48,0x00,0x06,0x45,0xDE};    //���ڷ��Ͷ�ȡָ��
    uint8_t Power_Reply_Fg;                                     //��Դ�巴����Ϣ��ʶ

    //�����Ϣ
    uint8_t TakeOver_Enable;                                    //�Ƿ���Ҫ�ӹ�
    uint8_t YBlink_Enable;                                      //�Ƿ�ҪӲ����
    uint8_t Error_YBlink_Enable;                                //�쳣�Ƿ�Ӳ����
    uint8_t Opt_VCheck_Enable;                                  //�ƿذ��Ƿ����ѹ���
    uint8_t Opt_ACheck_Enable;                                  //�ƿذ��Ƿ���������

    //�ƿذ巴����Ϣ
    struct Opt_Light_Reply_Structure  Opt_Reply_Buff[10];        //�ƿذ巴�������Ϣ����,10�����
    struct Opt_Light_Reply_ResultCount Opt_Reply_State[10];     //�ƿذ巴�������Ϣ���ݣ�10�����
    
    //Ӳ������Ϣ ??
    uint16_t YBlink_Count1;                                     //����Ӳ��������
    uint16_t YBlink_Count2;                                     //��Ӳ��������
    uint16_t YBlink_Count3;                                     //����Ӳ��������
    uint16_t YBlink_Count4;                                     //��Ӳ��������
    uint8_t YBlink_Fg;                                          //

//��������
    
    void IWDG_Init(uint8_t pre,uint_fast16_t reload);
    void System_Clock_Init(uint32_t pll);
    void IWDG_Feed(void);
    void TIM2_Init(uint16_t arr,uint16_t psc);
    void GPIO_Init(void);
    void CAN1_Init(void);
    void Power_CAN_Send(uint16_t sid,uint8_t data[8]);
    void UART2_Init(uint32_t baudrate);
    void JSY_DataRequest(void);
    void Seek_Pointer(void);
    void Power_Reply(void);
    void Light_Opt(uint8_t n);
    void Check_Opt_Reply(void);
#endif
