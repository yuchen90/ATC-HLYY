#ifndef __GLOBAL_VARIABLE_H__
#define __GLOBAL_VARIABLE_H__

#include "stdint.h"

uint32_t Sytem_Timer_Fg;        //��ʱ�������жϴ����ۼ�ֵ; �����
uint32_t Sytem_Timer_Fg1;       //��ʱ�������жϴ����ۼ�ֵ; ��CAN������ȡ����״̬�йأ������˸����ô��ֵ�ή��10000�ڣ�����������2s�� ��ֵ��20000��30000��
uint8_t Blink_Id;               //�����˸��ʶ 1����˸ 0������
uint8_t Blink_Id_Before;        //��һ�ε����˸��ʶ
uint8_t Board_Address;          //�ƿذ��ַ
uint8_t CAN_Buff[8];            //CANͨѶ���������ݻ���
uint8_t Channel_State[4];       //�ƿذ��ĸ�����ĵ����Ϣ����
uint8_t CAN_Send_Fg;            //CAN ����flag
uint8_t CAN_DataRead_Fg;        //1����ʾ�Ѿ�����CAN������CAN_Buff[8]�� 0���롮1���෴
// uint8_t LED_VACheck_Fg;   //�ƿذ� ��ǰ�����Ϣ ��ʶ�� ��CAN���Ľ�������,�Ƿ���Ҫ���������ذ壬1���ǣ� 0����     // ��ʱ���Բ���Ҫ���˶�������Ҫ���ߵ�Դ�壬�ڽӹ�ʱ��������
uint8_t VACheck_Fg;             //ռ�Ȳ�ѯ��ʶ Ϊ0ʱ����Ҫ�飬 ÿ�β�ѯ�� ��1 TIM2ÿ���ж϶�����0
uint16_t CAN_Send_Wait_Time;    //�ƿذ尴��Ŷ�Ӧ�Ļ���ʱ��
uint8_t CAN_VACheck_Send_Fg;    //�ƿذ��ƽ�� CAN������ʶ

// ռ�ȼ���ѹ����������ͳ��
// ����1
uint16_t R1_Volatge_Count;
uint16_t R1_Current_Count;
uint16_t Y1_Volatge_Count;
uint16_t Y1_Current_Count;
uint16_t G1_Volatge_Count;
uint16_t G1_Current_Count;
uint8_t R1_Volatge_Fg;
uint8_t R1_Current_Fg;
uint8_t Y1_Volatge_Fg;
uint8_t Y1_Current_Fg;
uint8_t G1_Volatge_Fg;
uint8_t G1_Current_Fg;
// ����2
uint16_t R2_Volatge_Count;
uint16_t R2_Current_Count;
uint16_t Y2_Volatge_Count;
uint16_t Y2_Current_Count;
uint16_t G2_Volatge_Count;
uint16_t G2_Current_Count;
uint8_t R2_Volatge_Fg;
uint8_t R2_Current_Fg;
uint8_t Y2_Volatge_Fg;
uint8_t Y2_Current_Fg;
uint8_t G2_Volatge_Fg;
uint8_t G2_Current_Fg;
// ����3
uint16_t R3_Volatge_Count;
uint16_t R3_Current_Count;
uint16_t Y3_Volatge_Count;
uint16_t Y3_Current_Count;
uint16_t G3_Volatge_Count;
uint16_t G3_Current_Count;
uint8_t R3_Volatge_Fg;
uint8_t R3_Current_Fg;
uint8_t Y3_Volatge_Fg;
uint8_t Y3_Current_Fg;
uint8_t G3_Volatge_Fg;
uint8_t G3_Current_Fg;
// ����4
uint16_t R4_Volatge_Count;
uint16_t R4_Current_Count;
uint16_t Y4_Volatge_Count;
uint16_t Y4_Current_Count;
uint16_t G4_Volatge_Count;
uint16_t G4_Current_Count;
uint8_t R4_Volatge_Fg;
uint8_t R4_Current_Fg;
uint8_t Y4_Volatge_Fg;
uint8_t Y4_Current_Fg;
uint8_t G4_Volatge_Fg;
uint8_t G4_Current_Fg;


//��������

void Led_Init(void);
void Led_Display(void);
//led.c

void Board_Address_Init(void);
uint8_t Board_Address_Get(void);
//Board_Address.c

void OPT_CAN_Init(void);
void OPT_CAN_Send(unsigned int sid,unsigned char data[]);
//CAN.c

void IWDG_Init(uint8_t pre,uint_fast16_t reload);
void IWDG_Feed(void);
//IWDG.c

void TIM2_Init(uint16_t arr,uint16_t psc);
//TIM2.c

void VACheck_GPIO_Init(void);
void Clear_Check_Count(void);
void VACheck(void);
//VACheck.c

void System_Clock_Init(u32 pll);
//System_Clock.c
#endif
