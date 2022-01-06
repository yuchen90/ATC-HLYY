#include "sys.h"
#include "delay.h"
#include "led.h"

/*void Delay(__IO uint32_t nCount);

void Delay(__IO uint32_t nCount)
{
  while(nCount--){}
}*/
void Led_Init(void);
void Light(void);

int main(void)
{
	HAL_Init();                    	 			//初始化HAL库    
  Stm32_Clock_Init(RCC_PLL_MUL9);   			//设置时钟,72M
	delay_init(72);
	Led_Init();

	while(1)
	{
	Light();
	}
}
