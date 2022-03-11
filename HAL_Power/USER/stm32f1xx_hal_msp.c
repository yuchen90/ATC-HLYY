#include "main.h"

/*------------------------------------------------------------------------------------------------------------------------------------
TIM
------------------------------------------------------------------------------------------------------------------------------------*/

/**
  * @brief TIM MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  * @param htim: TIM handle pointer
  * 定时器底册驱动，开启时钟，设置中断优先级
  * @retval None
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
  if(htim->Instance==TIMx)                         //确认开启时钟为TIM2
	{
	  TIMx_CLK_ENABLE();                             //使能TIM2时钟
		HAL_NVIC_SetPriority(TIMx_IRQn,3u,3u);         //设置中断优先级，抢占优先级3，子优先级3
		HAL_NVIC_EnableIRQ(TIMx_IRQn);                 //开启ITM2中断   
	}
}

/**
* @brief TIM_Base MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param htim: TIM_Base handle pointer
* @retval None
*/
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim)
{
  if(htim->Instance==TIMx)
  {
    //关闭TIM2时钟
    __HAL_RCC_TIM2_CLK_DISABLE();

    //关闭TIM2中断
    HAL_NVIC_DisableIRQ(TIM2_IRQn);
  }

}

/*------------------------------------------------------------------------------------------------------------------------------------
CAN
------------------------------------------------------------------------------------------------------------------------------------*/

/**
  * @brief CAN MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  *           - NVIC configuration for DMA interrupt request enable
  * @param hcan: CAN handle pointer
  * @retval None
  */
void HAL_CAN_MspInit(CAN_HandleTypeDef *hcan)
{
  GPIO_InitTypeDef GPIO_Init = {0u};

  CANx_CLK_ENABLE();
  CANx_GPIO_CLK_ENABLE();

  //Rx
  GPIO_Init.Pin = CANx_RX_PIN;
  GPIO_Init.Mode = GPIO_MODE_INPUT;
  GPIO_Init.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(CANx_RX_GPIO_PORT,&GPIO_Init);

  //Tx
  GPIO_Init.Pin = CANx_TX_PIN;
  GPIO_Init.Mode = GPIO_MODE_AF_PP;
  GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;         //10M带宽 信号速度为0.6MHz
  HAL_GPIO_Init(CANx_TX_GPIO_PORT,&GPIO_Init); 

  //CAN1 Rx Interrupt Init
  HAL_NVIC_SetPriority(CANx_RX_IRQn,2u,2u);         //抢占优先级：2
  HAL_NVIC_EnableIRQ(CANx_RX_IRQn);
}

/**
  * @brief CAN MSP De-Initialization
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO to their default state
  * @param hcan: CAN handle pointer
  * @retval None
  */
void HAL_CAN_MspDeInit(CAN_HandleTypeDef *hcan)
{
  // 外设时钟关闭
  __HAL_RCC_CAN1_CLK_DISABLE();

  // 失能外设时钟
  HAL_GPIO_DeInit(CANx_TX_GPIO_PORT, CANx_TX_PIN|CANx_RX_PIN);

  // 失能中断
  HAL_NVIC_DisableIRQ(CANx_RX_IRQn);
}

/*------------------------------------------------------------------------------------------------------------------------------------
USART
------------------------------------------------------------------------------------------------------------------------------------*/

/**
  * @brief USART MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  *           - NVIC configuration for DMA interrupt request enable
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  GPIO_InitTypeDef GPIO_Init = {0u};

	if(huart->Instance==UARTx)                         //如果是串口2，进行串口2 MSP初始化
	{
		UARTx_GPIO_CLK_ENABLE();			                    //使能GPIOA时钟
		UARTx_CLK_ENABLE;			                          //使能USART2时钟
	
    //发  
		GPIO_Init.Pin = UARTx_Tx_PIN;			              //PA2 
		GPIO_Init.Mode = GPIO_MODE_AF_PP;		              //复用推挽输出
		GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;            //低速
		HAL_GPIO_Init(UARTx_Tx_GPIO_PORT,&GPIO_Init);	  //初始化PA2

    //收
		GPIO_Init.Pin = UARTx_Rx_PIN;			              //PA3 
		GPIO_Init.Mode = GPIO_MODE_INPUT;	               //输入
    GPIO_Init.Pull = GPIO_NOPULL;                    //浮空
		HAL_GPIO_Init(UARTx_Rx_GPIO_PORT,&GPIO_Init);	  //初始化PA3

//#if EN_USART1_RX
		HAL_NVIC_SetPriority(UARTx_IRQn,0,2);			      //抢占优先级0，子优先级2
    HAL_NVIC_EnableIRQ(UARTx_IRQn);				          //使能USART2中断通道
//#endif	
  }
}

/**
  * @brief USART MSP De-Initialization
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO to their default state
  * @param hcan: CAN handle pointer
  * @retval None
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
  //关闭外设时钟
  __HAL_RCC_USART2_CLK_DISABLE();
  
  //失能管脚时钟
  HAL_GPIO_DeInit(UARTx_Tx_GPIO_PORT, UARTx_Tx_PIN|UARTx_Rx_PIN);

  //失能中断
  HAL_NVIC_DisableIRQ(UARTx_IRQn);
}
