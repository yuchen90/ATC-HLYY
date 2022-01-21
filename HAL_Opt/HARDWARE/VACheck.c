//以电流与电压反馈的占比时间来判断电流与电压是否正常
#include "main.h"
#include "declaration.h"

//对应电流与电压读取引脚初始化
void VACheak_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_Init;

    __HAL_RCC_GPIOA_CLK_ENABLE();           	//开启GPIOA时钟
	__HAL_RCC_GPIOB_CLK_ENABLE();               //开启GPIOB时钟
    __HAL_RCC_GPIOC_CLK_ENABLE();               //开启GPIOC时钟
    __HAL_RCC_GPIOD_CLK_ENABLE();               //开启GPIOD时钟

    //PA 2,4,6,8
    GPIO_Init.Pin = GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_8; 	
    GPIO_Init.Mode = GPIO_MODE_INPUT;  	    //输入
    GPIO_Init.Pull = GPIO_PULLUP;          	//上拉
    GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;    //高速
    HAL_GPIO_Init(GPIOA,&GPIO_Init);

    //PB 0，3，4，5，10，12，14
    GPIO_Init.Pin = GPIO_PIN_0|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_10|GPIO_PIN_12|GPIO_PIN_14; 
    GPIO_Init.Mode = GPIO_MODE_INPUT;  	    //输入
    GPIO_Init.Pull = GPIO_PULLUP;          	//上拉
    GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;    //高速
    HAL_GPIO_Init(GPIOB,&GPIO_Init);

    //PC 0，2，4，6，7，8，9，10，11，12，14
    GPIO_Init.Pin = GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_14;
    GPIO_Init.Mode = GPIO_MODE_INPUT;  	     //输入
    GPIO_Init.Pull = GPIO_PULLUP;          	//上拉
    GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;    //高速
    HAL_GPIO_Init(GPIOC,&GPIO_Init);

    //PD 2
    GPIO_Init.Pin = GPIO_PIN_2; 	
    GPIO_Init.Mode = GPIO_MODE_INPUT;  	    //输入
    GPIO_Init.Pull = GPIO_PULLUP;          	//上拉
    GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;    //高速
    HAL_GPIO_Init(GPIOD,&GPIO_Init);
}


