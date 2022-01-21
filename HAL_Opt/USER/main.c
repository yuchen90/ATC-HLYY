#include "main.h"
#include "global_variable.h"

//������
int main(void)
{
	HAL_Init();                    	 			//��ʼ��HAL��    
	Stm32_Clock_Init(RCC_PLL_MUL9);   			//����ʱ��,72M
	// delay_init(72); 							//delay.c �������SYSTICK ������ʱ����
	TIM2_Init(99u,71u);			//Tout=((10000)*(7200))/SYSCLOCK FREQUENCY us
	Board_Address_Init();
	OPT_CAN_Init();
	Led_Init();
	IWDG_Init(3u,1000u);						//���ö������Ź�ԼΪ1s ��Ϊ���õ�Ƶʱ�Ӳ�׼
	VACheak_GPIO_Init();

	BOARD_ADDRESS=0u;
	Board_Address_Get();
	CAN_Send_Fg=0u;LED_FeedBack_Fg=0u;CAN_Data_Read_Fg=0u;
	Blink_Id=0u;Blink_Id_Old=0u;
	Timer_Fg=20000u;Timer_Fg1=20000u;
	LED_Check_Fg=0u;
	while(1)
	{
		IWDG_Feed();
		
		if((Timer_Fg1%10000u) < 5000u)		//MCU_RUN ����ָʾ����˸Ƶ����������鶼һ��
		{
			MCU_RUN = LED_ON;				//��Timer_Fg1 �� Timer_Fg ��5000�μ����������ȵ��� ���ܱ�֤MCU_RUN���������һ��
		}
		else
		{
			MCU_RUN = LED_OFF;
		}

		if(Timer_Fg >= 20000u)			//û��CANͨѶ �� CANͨѶ�жϳ���2s ������� //���ݴ������ﰵ���� MCU_RUN �����෴
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
				Can_Buff[7] = 0x0bu;		//ȫ������ ���
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
				Can_Buff[7] = 0x1bu;		//ȫ������ ����
				Led_Display();
			}
		}

		// CANͨѶ���պ󣬰�����Ҫ���ƣ�ͬʱ���CAN�ձ�ʶ��
		if(CAN_Data_Read_Fg == 1u)
		{
		Led_Display();
		Timer_Fg = 0u;
		CAN_Data_Read_Fg = 0u;
		}
	}
}
