#include "main.h"
#include "global_variable.h"

//主函数
int main(void)
{
	HAL_Init();                    	 			//初始化HAL库    
	Stm32_Clock_Init(RCC_PLL_MUL9);   			//设置时钟,72M
	// delay_init(72); 							//delay.c 定义基于SYSTICK 计数延时函数
	TIM2_Init(99u,71u);			//Tout=((100)*(72))/SYSCLOCK FREQUENCY(units: MHz) us
	Board_Address_Init();
	OPT_CAN_Init();
	Led_Init();
	IWDG_Init(3u,1000u);						//设置独立看门狗约为1s 因为内置低频时钟不准
	VACheck_GPIO_Init();

	BOARD_ADDRESS=0u;
	Board_Address_Get();
	CAN_Send_Fg=0u; /*LED_FeedBack_Fg=0u;*/ CAN_Data_Read_Fg=0u;
	Blink_Id=0u; Blink_Id_Before=0u;
	Timer_Fg=20000u; Timer_Fg1=20000u;
	// LED_VACheck_Fg=0u;
	VACheck_Fg = 0u; CAN_VACheck_Send_Fg = 0u;
	while(1)
	{
		IWDG_Feed();
		
		if((Timer_Fg1%10000u) < 5000u)		//MCU_RUN 工作指示灯闪烁频率与其余灯组都一样， 判断与led.c line 66&67 有关
		{
			MCU_RUN = LED_OFF;				//因Timer_Fg1 比 Timer_Fg 少5000次计数，所以先点亮 才能保证MCU_RUN暗灭与灯组一致 
		}
		else
		{
			MCU_RUN = LED_ON;
		}

		if(Timer_Fg >= 20000u)			//没有CAN通讯 或 CAN通讯中断超过2s 灯组黄闪 //杭州代码这里暗灭与 MCU_RUN 正好相反
		{
			if((Timer_Fg%10000) == 0u) 
			{
				Can_Buff[0] = 0x6du;
				Can_Buff[1] = 0xdbu;
				Can_Buff[2] = 0xb6u;
				Can_Buff[3] = 0x6du;
				Can_Buff[4] = 0xdbu;
				Can_Buff[5] = 0xb6u;
				Can_Buff[6] = 0x6du;
				Can_Buff[7] = 0x0bu;		//全部黄闪 灭灯
				Led_Display();
			}
			else if((Timer_Fg%10000) == 5000u)
			{
				Can_Buff[0] = 0x6du;
				Can_Buff[1] = 0xdbu;
				Can_Buff[2] = 0xb6u;
				Can_Buff[3] = 0x6du;
				Can_Buff[4] = 0xdbu;
				Can_Buff[5] = 0xb6u;
				Can_Buff[6] = 0x6du;
				Can_Buff[7] = 0x1bu;		//全部黄闪 亮灯
				Led_Display();
			}
		}

		// CAN通讯接收后，按报文要求点灯，同时清除CAN收标识符
		if(CAN_Data_Read_Fg == 1u)
		{
		Led_Display();
		Timer_Fg = 0u;
		CAN_Data_Read_Fg = 0u;
		CAN_VACheck_Send_Fg = 2u;			//让灯控板一直反馈点灯结果
		Clear_Check_Count();
		CAN_Send_Wait_Time = 400u + BOARD_ADDRESS*20u;
		}
		if(CAN_VACheck_Send_Fg == 2u)
		{
			VACheck();
		}
	}
}
