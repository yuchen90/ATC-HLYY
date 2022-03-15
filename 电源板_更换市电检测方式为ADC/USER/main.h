#ifndef __MAIN_H__
#define __MAIN_H__
////////////////////////////////////////////////////
/////系统运行变量
	u32 timerfg;
	u32 timerfg1;
	u8 canreadfg;
	u8 nowcheckfg;
////////////////////////////////////////////////////
/////灯色输出BUFF
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
/////接管信息
	uint32_t checksum;	//校验码
	uint16_t arraynu;		//接管数据的个数
	uint16_t framenum;		//需要接受的帧个数
	

	struct TakeOverStr TakeOverStruse[160];
	uint16_t TakeOverNumbuse;				//总接管节拍
	uint16_t TakeOverPointeruse;		//接管指针
	struct TakeOverStr TakeOverStrstorage[160];
////////////////////////////////////////////////////
/////发包信息
	uint8_t runtime;
	
////////////////////////////////////////////////////
/////电压电流检测
	uint8_t JSYReadbuff[40];
	uint8_t JSYReadFg;
	uint16_t  cheakmdfg;
	
////////////////////////////////////////////////////
/////检查变量定义	
	uint8_t JSYReadbuff[40];
	uint8_t JSYReadFg;
	uint16_t  cheakmdfg;
////////////////////////////////////////////////////
/////检查信息
	uint8_t TakeOverorder;				//是否需要接管命令
	uint8_t Y_FLASHorder;					//是否硬件黄闪命令
	uint8_t checkY_FLASHorder;		//异常是否需要黄闪指令
	uint8_t checkCurrentorder;		//电流检测
	uint8_t checkVoltageorder;		//电压检测
	struct CheckreplyStr Checkreplybuff[10];//回复数组
	struct Checkrstate	Checkrstatebuff[10];//回复状态
	
	uint16_t Voltage_R1_numb;
	uint16_t Voltage_R2_numb;
	
	uint16_t Voltage_R3_numb;
	uint16_t Voltage_R4_numb;
	uint8_t Voltage_R1_fg;
#endif	