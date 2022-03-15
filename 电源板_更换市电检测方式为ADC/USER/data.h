#ifndef __DATA_H__
#define __DATA_H__
////////////////////////////////////////////////////
/////ϵͳ���б���
	extern u32 timerfg;
	extern u32 timerfg1;
	extern u8 canreadfg;
	extern u8 nowcheckfg;
////////////////////////////////////////////////////
/////��ɫ���BUFF
	extern u8 CanId_IDE;
	extern u8 CanId_SRR;
	extern u8 CanId_RTR;
	extern u8 CanId_CANtype;
	extern u32 CanId_DataNumber;
	
	extern u8 canbuff[16];
	extern u8 cmd[15];
	extern u8 flashfg;
	extern u8 flashfgbf;
	extern u8 cheakfg;
	extern u8 cheakfg2;
	extern u8 cheakfgf;
	extern u8 cheakfgS;
////////////////////////////////////////////////////
/////�ӹ���Ϣ
	extern uint32_t checksum;	//У����
	extern uint16_t arraynu;		//�ӹ����ݵĸ���
	extern uint16_t framenum;		//��Ҫ���ܵ�֡����
	
	extern  struct  TakeOverStr TakeOverStruse[160];
	extern  uint16_t TakeOverNumbuse;
	extern uint16_t TakeOverPointeruse;
	extern struct TakeOverStr TakeOverStrstorage[160];
////////////////////////////////////////////////////
/////������Ϣ
	extern uint8_t runtime;
	
////////////////////////////////////////////////////
/////��ѹ�������
	extern uint8_t JSYReadbuff[40];
	extern uint8_t JSYReadFg;
	extern uint16_t  cheakmdfg;
	
////////////////////////////////////////////////////
/////�����Ϣ
	extern uint8_t TakeOverorder;				//�Ƿ���Ҫ�ӹ�����
	extern uint8_t Y_FLASHorder;					//�Ƿ�Ӳ����������
	extern uint8_t checkY_FLASHorder;		//�쳣�Ƿ���Ҫ����ָ��
	extern uint8_t checkCurrentorder;		//�������
	extern uint8_t checkVoltageorder;		//��ѹ���
	extern struct CheckreplyStr Checkreplybuff[10];
	extern struct Checkrstate	Checkrstatebuff[10];
	
	extern uint16_t Voltage_R1_numb;
	extern uint16_t Voltage_R2_numb;
	
	extern uint16_t Voltage_R3_numb;
	extern uint16_t Voltage_R4_numb;
	
	extern uint8_t Voltage_R1_fg;
#endif	

