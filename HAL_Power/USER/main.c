#include "main.h"
#include "global_variable.h"
//ȫ�ֱ��� ����ʼֵ��ҪΪ�㣬���Բ���ʼ������0�� CĬ�ϳ�ʼ��Ϊ0

//DEBUG
uint32_t w,e,t,r;
//DEBUG_END

//������
int main(void)
{
	HAL_Init();
	Stm32_Clock_Init(RCC_PLL_MUL9);			//systemclk 72MHz
	IWDG_Init(4u, 500u);
	TIM2_Init(99u, 71u);					//1us 1���ж�
	GPIO_Init();
	CAN1_Init();
	UART2_Init(4800u);

	JSY_DataRequest();
	while (1)
	{
		IWDG_Feed();						//ι��

		if(System_Time_Fg1%10000u < 5000u)
			MCU_RUN=LED_ON;
		else	
			MCU_RUN=LED_OFF;

		if(CAN_DataRead_Fg == 1u)
		{
			Seek_Pointer();
			JSY_MK163_ReadRequest_Fg++;
			if(JSY_MK163_ReadRequest_Fg >= 4u)
			{
				JSY_MK163_ReadRequest_Fg=0u;
				JSY_DataRequest();
			}
			System_Time_Fg=0u;
			CAN_DataRead_Fg=0u;
			Power_Reply_Fg=2u;
		}
		if(Power_Reply_Fg == 2u)
			Power_Reply();
		
		if((System_Time_Fg < 1200u) && (System_Time_Fg > 600u))
		{
			if(Y_FLASH_FEEDBACK == 0u)
				YBlink_Count2++;
			else
				YBlink_Count4++;
		}

		if((System_Time_Fg > 600u) && (System_Time_Fg < 1200u))
		{
			if(Y_FLASH_FEEDBACK == 0u)
				YBlink_Count1++;
			else
				YBlink_Count3++;
		}

		////////////////////////////////////////////////////�ӹ�////////////////////////////////////////////
		if((TakeOver_Enable == 1u) && (TakeOver_DataNum > 0u))
		{
			if(System_Time_Fg == 15000u)
			{
				CAN_Tx_LED=LED_ON;
				CAN_Rx_LED=LED_OFF;
				Light_Opt(0u);
				CAN_Tx_LED=LED_OFF;
				CAN_Rx_LED=LED_ON;
			}
			else if(System_Time_Fg == 17500u)
			{
				CAN_Tx_LED=LED_ON;
				CAN_Rx_LED=LED_OFF;
				Light_Opt(1u);
				CAN_Tx_LED=LED_OFF;
				CAN_Rx_LED=LED_ON;
			}
			else if(System_Time_Fg == 20000u)
			{
				CAN_Tx_LED=LED_ON;
				CAN_Rx_LED=LED_OFF;
				Light_Opt(2u);
				CAN_Tx_LED=LED_OFF;
				CAN_Rx_LED=LED_ON;
			}
			else if(System_Time_Fg == 22500u)
			{
				CAN_Tx_LED=LED_ON;
				CAN_Rx_LED=LED_OFF;
				Light_Opt(3u);
				CAN_Tx_LED=LED_OFF;
				CAN_Rx_LED=LED_ON;
				RunTime++;
				if(RunTime >= TakeOver_Structure_Use[TakeOver_Pointer].Duration)
				{
					RunTime=0u;
					TakeOver_Pointer++;
					if(TakeOver_Pointer >= TakeOver_DataNum)
						TakeOver_Pointer=0u;
				}
			}
			
			if((System_Time_Fg >= 15000u) && (System_Time_Fg%2500 == 1000u))
			{
				Check_Opt_Reply();
			}
		}
	}
}
