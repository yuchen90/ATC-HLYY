#include "main.h"
#include "global_variable.h"

//主函数
int main(void)
{
	HAL_Init();                    	 				//初始化HAL库    
	System_Clock_Init(RCC_PLL_MUL9);   				//设置时钟,72M
	TIM2_Init(99u,71u);								//Tout=((100)*(72))/SYSCLOCK FREQUENCY(units: MHz) us
	Board_Address_Init();
	OPT_CAN_Init();
	Led_Init();
	IWDG_Init(4u,500u);								//设置独立看门狗约为1s 因为内置低频时钟不准
	VACheck_GPIO_Init();

	Board_Address_Get();
	Sytem_Timer_Fg=20000u; Sytem_Timer_Fg1=20000u;
	
	while(1)
	{
		IWDG_Feed();
		
		if((Sytem_Timer_Fg1%10000u) < 5000u)		
		{
			MCU_RUN=LED_ON;							//MCU工作指示灯
		}
		else
		{
			MCU_RUN=LED_OFF;
		}

		if(Sytem_Timer_Fg >= 20000u)				//没有CAN通讯 或 CAN通讯中断超过2s 灯组黄闪
		{
			if((Sytem_Timer_Fg%10000) == 0u) 
			{
				CAN_Buff[0]=0x6du;
				CAN_Buff[1]=0xdbu;
				CAN_Buff[2]=0xb6u;
				CAN_Buff[3]=0x6du;
				CAN_Buff[4]=0xdbu;
				CAN_Buff[5]=0xb6u;
				CAN_Buff[6]=0x6du;
				CAN_Buff[7]=0x0bu;					//全部黄闪 灭灯
				Led_Display();
			}
			else if((Sytem_Timer_Fg%10000) == 5000u)
			{
				CAN_Buff[0]=0x6du;
				CAN_Buff[1]=0xdbu;
				CAN_Buff[2]=0xb6u;
				CAN_Buff[3]=0x6du;
				CAN_Buff[4]=0xdbu;
				CAN_Buff[5]=0xb6u;
				CAN_Buff[6]=0x6du;
				CAN_Buff[7]=0x1bu;					//全部黄闪 亮灯
				Led_Display();
			}
		}

		// CAN通讯接收后，按报文要求点灯，同时清除CAN收标识符
		if(CAN_DataRead_Fg == 1u)
		{
			CAN_Rx_LED = LED_OFF;
			Led_Display();
			Sytem_Timer_Fg=0u;
			CAN_DataRead_Fg=0u;
			CAN_VACheck_Send_Fg=2u;					//让灯控板一直反馈点灯结果
			Clear_Check_Count();
			CAN_Send_Wait_Time=400u+Board_Address*20u;
		}
		if(CAN_VACheck_Send_Fg == 2u)
		{
			VACheck();
		}
	}
}
