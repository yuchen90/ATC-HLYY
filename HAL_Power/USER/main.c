#include "main.h"
#include "global_variable.h"
//ȫ�ֱ��� ����ʼֵ��ҪΪ�㣬���Բ���ʼ������0�� CĬ�ϳ�ʼ��Ϊ0

//DEBUG
uint32_t w,e,t,r;
extern UART_HandleTypeDef UART2_Handle;
extern uint8_t UART_Rx_Buff[UART_RxDataSize];
//DEBUG_END

//������
int main(void)
{
	HAL_Init();
	Stm32_Clock_Init(RCC_PLL_MUL9);			//systemclk 72MHz
	// IWDG_Init(64u, 500u);
	// TIM2_Init(99u, 71u);
	UART_Init(4800u);
	// GPIO_Init();

	while (1)
	{
		// IWDG_Feed();						//ι��
		w++;
		JSY_DataRequest();
		JSY_MK163_ReadNum = 0u;
		HAL_Delay(2000);
	}
}
