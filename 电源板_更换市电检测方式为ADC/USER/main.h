#ifndef __MAIN_H__
#define __MAIN_H__
////////////////////////////////////////////////////
/////ϵͳ���б���
	u32 timerfg;
	u32 timerfg1;
	u8 canreadfg;
	u8 nowcheckfg;
////////////////////////////////////////////////////
/////��ɫ���BUFF
	u8 CanId_IDE;
	u8 CanId_SRR;
	u8 CanId_RTR;
	uint8_t CanId_CANtype;
	uint32_t CanId_DataNumber;
	
	u8 canbuff[16];
	u8 cmd[15];
	u8 flashfg;
	u8 flashfgbf;
	u8 cheakfg;
	u8 cheakfg2;
	
	u8 cheakfgf;
	u8 cheakfgS;
////////////////////////////////////////////////////
/////�ӹ���Ϣ
	uint32_t checksum;	//У����
	uint16_t arraynu;		//�ӹ����ݵĸ���
	uint16_t framenum;		//��Ҫ���ܵ�֡����
	

	struct TakeOverStr TakeOverStruse[160];
	uint16_t TakeOverNumbuse;				//�ܽӹܽ���
	uint16_t TakeOverPointeruse;		//�ӹ�ָ��
	struct TakeOverStr TakeOverStrstorage[160];
////////////////////////////////////////////////////
/////������Ϣ
	uint8_t runtime;
	
////////////////////////////////////////////////////
/////��ѹ�������
	uint8_t JSYReadbuff[40];
	uint8_t JSYReadFg;
	uint16_t  cheakmdfg;
	
////////////////////////////////////////////////////
/////����������	
	uint8_t JSYReadbuff[40];
	uint8_t JSYReadFg;
	uint16_t  cheakmdfg;
////////////////////////////////////////////////////
/////�����Ϣ
	uint8_t TakeOverorder;				//�Ƿ���Ҫ�ӹ�����
	uint8_t Y_FLASHorder;					//�Ƿ�Ӳ����������
	uint8_t checkY_FLASHorder;		//�쳣�Ƿ���Ҫ����ָ��
	uint8_t checkCurrentorder;		//�������
	uint8_t checkVoltageorder;		//��ѹ���
	struct CheckreplyStr Checkreplybuff[10];//�ظ�����
	struct Checkrstate	Checkrstatebuff[10];//�ظ�״̬
	
	uint16_t Voltage_R1_numb;
	uint16_t Voltage_R2_numb;
	
	uint16_t Voltage_R3_numb;
	uint16_t Voltage_R4_numb;
	uint8_t Voltage_R1_fg;
#endif	