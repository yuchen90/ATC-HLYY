#include "sys.h"
#include "delay.h"
#include "led.h"

/*void Delay(__IO uint32_t nCount);

void Delay(__IO uint32_t nCount)
{
  while(nCount--){}
}*/
void Led_Init(void);

int main(void)
{
    HAL_Init();                    	 			//��ʼ��HAL��    
    Stm32_Clock_Init(RCC_PLL_MUL9);   			//����ʱ��,72M
	Led_Init();

	while(1)
	{

	}
}
