//������Ҫʹ�õ�ȫ�ֱ���
#ifndef __MAIN_H__
#define __MAIN_H__

extern unsigned int Timer_Fg;        //��ʱ�������ۼ�ֵ
extern unsigned int Timer_Fg1; 
extern unsigned char Blink_Id;       //�����˸��ʶ 1����˸ 0������
extern unsigned char Blink_Id_Old;   //��һ�ε����˸��ʶ
extern unsigned char BOARD_ADDRESS; //�ƿذ��ַ
extern unsigned char Can_Buff[8];    //CANͨѶ���������ݻ���
extern unsigned char Light_Buff[4]; //�ƿذ��ĸ�����ĵ����Ϣ����
extern unsigned char CAN_Send_Fg;   //CAN ����flag

//��������
//led.c
void Led_Init(void);
void Light(void);
//Board_Address.c
void Board_Address_Init(void);
uint8_t Board_Address_Get(void);
//CAN.c
void OPT_CAN_Init(void);
void OPT_CAN_Send(uint32_t SID,uint8_t data[8]);

#endif
