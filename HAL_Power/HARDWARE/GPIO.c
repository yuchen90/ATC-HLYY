#include "main.h"
#include "declaration.h"

/**
  * @brief CAN MSP Initialization
  *        �õ���GPIO�ܽ�MSP��ʼ��
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

	__HAL_RCC_GPIOB_CLK_ENABLE();                     //����GPIOBʱ��
	__HAL_RCC_GPIOC_CLK_ENABLE();                     //����GPIOCʱ��

  //���
  //PB1��PB10,PB11
  GPIO_Init.Pin = GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_11; 	
	GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;     	      //�������
	GPIO_Init.Pull = GPIO_NOPULL;          	          //���NO PULL
	GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;            //���٣�DC���
    HAL_GPIO_Init(GPIOB,&GPIO_Init);
  //PC6
  GPIO_Init.Pin = GPIO_PIN_6; 	
  GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;  	          //�������
  GPIO_Init.Pull = GPIO_NOPULL;          	          //���NO PULL
  GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;            //���٣�DC���
  HAL_GPIO_Init(GPIOC,&GPIO_Init);

  //����
  //PC10
	GPIO_Init.Pin = GPIO_PIN_10; 	
	GPIO_Init.Mode = GPIO_MODE_INPUT;  	                //����
	GPIO_Init.Pull = GPIO_PULLUP;          	            //����
	HAL_GPIO_Init(GPIOC,&GPIO_Init);
}
