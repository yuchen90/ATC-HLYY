#ifndef __GLOBAL_VARIABLE_H__
#define __GLOBAL_VARIABLE_H__

#include "stdint.h"

uint32_t Timer_Fg;        //��ʱ�������ۼ�ֵ
uint32_t Timer_Fg1; 
uint8_t Blink_Id;       //�����˸��ʶ 1����˸ 0������
uint8_t Blink_Id_Old;   //��һ�ε����˸��ʶ
uint8_t BOARD_ADDRESS; //�ƿذ��ַ
uint8_t Can_Buff[8];    //CANͨѶ���������ݻ���
uint8_t Light_Buff[4]; //�ƿذ��ĸ�����ĵ����Ϣ����
uint8_t CAN_Send_Fg;   //CAN ����flag
uint8_t CAN_Data_Read_Fg; //1����ʾ�Ѿ�����CAN������Can_Buff[8]�� 0���롮1���෴
uint8_t LED_FeedBack_Fg; //��ʾ�ƿذ����Ƿ���Ҫ���������ذ壬1���ǣ� 0����

#endif
