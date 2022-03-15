#ifndef __COMMON_H__
#define __COMMON_H__
//////////////////////////////
#define Version 1



#define LON		1
#define LOFF	0


#define SON		1
#define SOFF		0


#define OrderON 	1
#define OrderOFF 	0


//指示灯IO定义

	#define MCU_RUN_PORT GPIOB
	#define MCU_RUN_PIN	GPIO_Pin_1
	

	
	#define CAN_T_LED_PORT GPIOB
	#define CAN_T_LED_PIN	GPIO_Pin_10

	#define CAN_R_LED_PORT GPIOB
	#define CAN_R_LED_PIN	GPIO_Pin_11
	
	#define Y_FLASH_PORT GPIOC
	#define Y_FLASH_PIN	GPIO_Pin_6
	
	#define Y_F_Voltage_PORT 	GPIOC
	#define Y_F_Voltage_PIN		GPIO_Pin_10
	
	#define MCU_RUN(x)      	GPIO_WriteBit(MCU_RUN_PORT,MCU_RUN_PIN,x)
	#define CAN_R_LED(x)      GPIO_WriteBit(CAN_T_LED_PORT,CAN_T_LED_PIN,x)
	#define CAN_T_LED(x)      GPIO_WriteBit(CAN_R_LED_PORT,CAN_R_LED_PIN,x)	
	#define Y_FLASH(x)				GPIO_WriteBit(Y_FLASH_PORT,Y_FLASH_PIN,x)

	#define Y_F_Voltage GPIO_ReadInputDataBit(Y_F_Voltage_PORT,Y_F_Voltage_PIN)



	#define Errortime 12
/////////////////////////////////////////////////////////////////
//////////********时段结构体变量定义段********///////////////////
/////////////////////////////////////////////////////////////////
	typedef struct TakeOverStr
	{
		u8 duration;
		u8 cmd[15];
	} TakeOverStr;
	
	typedef struct CheckreplyStr
	{
		uint8_t start;
		uint8_t cmd[8];
		
		uint8_t nowcolour[4];
		uint8_t nowstart[4];
		uint8_t nowstartRV[4];
		uint8_t nowstartRC[4];
		uint8_t nowstartYV[4];
		uint8_t nowstartYC[4];
		uint8_t nowstartGV[4];
		uint8_t nowstartGC[4];
		
	} CheckreplyStr;
	
	typedef struct Checkrstate
	{
		uint8_t CheckorNO;		//是否需要检测
		uint8_t	Replystate;
		uint8_t	Replytime;
		/*
		uint8_t	RedVstate[4];
		uint8_t	YellowVstate[4];
		uint8_t	GreedVstate[4];
		
		uint8_t	RedCstate[4];
		uint8_t	YellowCstate[4];
		uint8_t	GreedCstate[4];*/
		
		uint8_t	RedVtime[4];
		uint8_t	YellowVtime[4];
		uint8_t	GreedVtime[4];
		
		uint8_t	RedCtime[4];
		uint8_t	YellowCtime[4];		
		uint8_t	GreedCtime[4];
		
		uint8_t	FRedVtime[4];		
		uint8_t	FYellowVtime[4];		
		uint8_t	FGreedVtime[4];
		
		uint8_t	FRedCtime[4];		
		uint8_t	FYellowCtime[4];		
		uint8_t	FGreedCtime[4];
		
	} Checkrstate;
	
//////////////////
/* 信号故障检测逻辑
	1. 没有电绿灯   绿灯有电压
	2.   点亮绿灯   红灯有电压
	3.   点亮红灯   红灯无电流
	4      点黄灯   黄灯无电流
	
	连续12次
*/	
	
	
	
#endif	

