////////////////////////////////////////////////////////////////
/*
IO口初始化
*/
////////////////////////////////////////////////////////////////
#include "stm32f10x.h"
#include "common.h"
#include "data.h"




void init_gpio()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//输出定义
	{

		//GPIOB
		{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
		
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 |GPIO_Pin_11 |GPIO_Pin_10 ;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOB, &GPIO_InitStruct);
		}
		//GPIOC
		{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 
		
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOC, &GPIO_InitStruct);
		}
		
		//GPIOC
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 
			
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
			
			GPIO_Init(GPIOC, &GPIO_InitStruct);
		}
		
	}

	
}