#include "main.h"
#include "global_variable.h"

//��������
//led.c
void Led_Init(void);
void Led_Display(void);
//Board_Address.c
void Board_Address_Init(void);
unsigned char Board_Address_Get(void);
//CAN.c
void OPT_CAN_Init(void);
void OPT_CAN_Send(unsigned int SID,unsigned char data[]);
void TIM2_Init(void);

//������
int main(void)
{
	HAL_Init();                    	 			//��ʼ��HAL��    
	Stm32_Clock_Init(RCC_PLL_MUL9);   			//����ʱ��,72M
	// delay_init(72); 							//delay.c �������SYSTICK ������ʱ����
	TIM2_Init();
	Board_Address_Init();
	OPT_CAN_Init();
	Led_Init();
	
	BOARD_ADDRESS=0u;
	Board_Address_Get();
	CAN_Send_Fg=0u;LED_FeedBack_Fg=0u;CAN_Data_Read_Fg=0u;
	Blink_Id=0u;Blink_Id_Old=0u;
	Timer_Fg=10000u,Timer_Fg1=10000u;
	while(1)
	{
		if(CAN_Data_Read_Fg == 1u)
		{
		Led_Display();
		CAN_Data_Read_Fg=0u;
		}
		MCU_RUN = LED_ON;

	}
}
