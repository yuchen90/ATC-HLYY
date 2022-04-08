#include "main.h"
#include "global_variable.h"

//������
int main(void)
{
	HAL_Init();                    	 				//��ʼ��HAL��    
	System_Clock_Init(RCC_PLL_MUL9);   				//����ʱ��,72M
	TIM2_Init(99u,71u);								//Tout=((100)*(72))/SYSCLOCK FREQUENCY(units: MHz) us
	Board_Address_Init();
	OPT_CAN_Init();
	Led_Init();
	IWDG_Init(4u,500u);								//���ö������Ź�ԼΪ1s ��Ϊ���õ�Ƶʱ�Ӳ�׼
	VACheck_GPIO_Init();

	Board_Address_Get();
	Sytem_Timer_Fg=20000u; Sytem_Timer_Fg1=20000u;
	
	while(1)
	{
		IWDG_Feed();
		
		if((Sytem_Timer_Fg1%10000u) < 5000u)		
		{
			MCU_RUN=LED_ON;							//MCU����ָʾ��
		}
		else
		{
			MCU_RUN=LED_OFF;
		}

		if(Sytem_Timer_Fg >= 20000u)				//û��CANͨѶ �� CANͨѶ�жϳ���2s �������
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
				CAN_Buff[7]=0x0bu;					//ȫ������ ���
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
				CAN_Buff[7]=0x1bu;					//ȫ������ ����
				Led_Display();
			}
		}

		// CANͨѶ���պ󣬰�����Ҫ���ƣ�ͬʱ���CAN�ձ�ʶ��
		if(CAN_DataRead_Fg == 1u)
		{
			CAN_Rx_LED = LED_OFF;
			Led_Display();
			Sytem_Timer_Fg=0u;
			CAN_DataRead_Fg=0u;
			CAN_VACheck_Send_Fg=2u;					//�õƿذ�һֱ������ƽ��
			Clear_Check_Count();
			CAN_Send_Wait_Time=400u+Board_Address*20u;
		}
		if(CAN_VACheck_Send_Fg == 2u)
		{
			VACheck();
		}
	}
}
