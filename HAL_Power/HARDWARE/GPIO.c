#include "main.h"
#include "declaration.h"

/**
  * @brief CAN MSP Initialization
  *        用到的GPIO管脚MSP初始化
  *           - MCU_RUN           PB1
  *           - CAN_RX_LED        PB11
  *           - CAN_TX_LED        PB10
  *           - Y_FLASH_ENABLE    PC6
  *           - Y_FLASH_FEEDBACK  PC10
  * @param None
  * @retval None
  */
void GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_Init;

	__HAL_RCC_GPIOB_CLK_ENABLE();                     //开启GPIOB时钟
	__HAL_RCC_GPIOC_CLK_ENABLE();                     //开启GPIOC时钟

  //输出
  //PB1，PB10,PB11
  GPIO_Init.Pin = GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_11; 	
	GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;     	      //推挽输出
	GPIO_Init.Pull = GPIO_NOPULL;          	          //输出NO PULL
	GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;            //低速，DC输出
    HAL_GPIO_Init(GPIOB,&GPIO_Init);
  //PC6
  GPIO_Init.Pin = GPIO_PIN_6; 	
  GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;  	          //推挽输出
  GPIO_Init.Pull = GPIO_NOPULL;          	          //输出NO PULL
  GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;            //低速，DC输出
  HAL_GPIO_Init(GPIOC,&GPIO_Init);

  //输入
  //PC10
	GPIO_Init.Pin = GPIO_PIN_10; 	
	GPIO_Init.Mode = GPIO_MODE_INPUT;  	                //输入
	GPIO_Init.Pull = GPIO_PULLUP;          	            //上拉
	HAL_GPIO_Init(GPIOC,&GPIO_Init);
}
