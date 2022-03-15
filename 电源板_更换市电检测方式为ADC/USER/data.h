#ifndef __DATA_H__
#define __DATA_H__
////////////////////////////////////////////////////
/////系统运行变量
	extern u32 timerfg;
	extern u32 timerfg1;
	extern u8 canreadfg;
	extern u8 nowcheckfg;
////////////////////////////////////////////////////
/////灯色输出BUFF
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
/////接管信息
	extern uint32_t checksum;	//校验码
	extern uint16_t arraynu;		//接管数据的个数
	extern uint16_t framenum;		//需要接受的帧个数
	
	extern  struct  TakeOverStr TakeOverStruse[160];
	extern  uint16_t TakeOverNumbuse;
	extern uint16_t TakeOverPointeruse;
	extern struct TakeOverStr TakeOverStrstorage[160];
////////////////////////////////////////////////////
/////发包信息
	extern uint8_t runtime;
	
////////////////////////////////////////////////////
/////电压电流检测
	extern uint8_t JSYReadbuff[40];
	extern uint8_t JSYReadFg;
	extern uint16_t  cheakmdfg;
	
////////////////////////////////////////////////////
/////检查信息
	extern uint8_t TakeOverorder;				//是否需要接管命令
	extern uint8_t Y_FLASHorder;					//是否硬件黄闪命令
	extern uint8_t checkY_FLASHorder;		//异常是否需要黄闪指令
	extern uint8_t checkCurrentorder;		//电流检测
	extern uint8_t checkVoltageorder;		//电压检测
	extern struct CheckreplyStr Checkreplybuff[10];
	extern struct Checkrstate	Checkrstatebuff[10];
	
	extern uint16_t Voltage_R1_numb;
	extern uint16_t Voltage_R2_numb;
	
	extern uint16_t Voltage_R3_numb;
	extern uint16_t Voltage_R4_numb;
	
	extern uint8_t Voltage_R1_fg;
#endif	

