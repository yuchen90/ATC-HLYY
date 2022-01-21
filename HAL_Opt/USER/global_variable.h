#ifndef __GLOBAL_VARIABLE_H__
#define __GLOBAL_VARIABLE_H__

#include "stdint.h"

uint32_t Timer_Fg;        //��ʱ�������жϴ����ۼ�ֵ; �����
uint32_t Timer_Fg1;       //��ʱ�������жϴ����ۼ�ֵ; ��CAN������ȡ����״̬�йأ������˸����ô��ֵ�ή��10000�ڣ�����������2s�� ��ֵ��20000��30000��
uint8_t Blink_Id;       //�����˸��ʶ 1����˸ 0������
uint8_t Blink_Id_Old;   //��һ�ε����˸��ʶ
uint8_t BOARD_ADDRESS; //�ƿذ��ַ
uint8_t Can_Buff[8];    //CANͨѶ���������ݻ���
uint8_t Light_Buff[4]; //�ƿذ��ĸ�����ĵ����Ϣ����
uint8_t CAN_Send_Fg;   //CAN ����flag
uint8_t CAN_Data_Read_Fg; //1����ʾ�Ѿ�����CAN������Can_Buff[8]�� 0���롮1���෴
uint8_t LED_FeedBack_Fg; //��ʾ�ƿذ����Ƿ���Ҫ���������ذ壬1���ǣ� 0����
uint8_t LED_Check_Fg;    //�ƿذ� ��ǰ�����Ϣ ��ʶ�� ����������������⺬��

//��������
//led.c
void Led_Init(void);
void Led_Display(void);
//Board_Address.c
void Board_Address_Init(void);
uint8_t Board_Address_Get(void);
//CAN.c
void OPT_CAN_Init(void);
void OPT_CAN_Send(unsigned int SID,unsigned char data[]);
//IWDG.c
void IWDG_Init(uint8_t pre,uint_fast16_t reload);
void IWDG_Feed(void);
//TIM2.c
void TIM2_Init(uint16_t arr,uint16_t psc);
//VACheck.c
void VACheak_GPIO_Init(void);

#endif
