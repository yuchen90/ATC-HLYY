#include "main.h"
#include "global_variable.h"
//全局变量 若初始值需要为零，可以不初始化等于0， C默认初始化为0

//主函数
int main(void)
{
	HAL_Init();
	Stm32_Clock_Init(RCC_PLL_MUL9);			//systemclk 72MHz
	IWDG_Init(64u, 500u);
	TIM2_Init(99u, 71u);
	USART_Init(4800u);
	GPIO_Init();

	while (1)
	{
		IWDG_Feed();						//喂狗
	}
}
