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
  GPIO_InitTypeDef GPIO_Init;

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
  GPIO_Init.Speed = GPIO_SPEED_FREQ_MEDIUM;         //10M带宽 信号速度为0.6MHz
  GPIO_Init.Pull = GPIO_NOPULL;
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
  // 重置外设
  CANx_FORCE_RESET();
  CANx_RELEASE_RESET();

  // 失能外设时钟
  HAL_GPIO_DeInit(CANx_TX_GPIO_PORT, CANx_TX_PIN);
  HAL_GPIO_DeInit(CANx_RX_GPIO_PORT, CANx_RX_PIN);

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
  GPIO_InitTypeDef GPIO_Init;

	if(huart->Instance==UARTx)                         //如果是串口2，进行串口2 MSP初始化
	{
		UARTx_GPIO_CLK_ENABLE();			                    //使能GPIOA时钟
		UARTx_CLK_ENABLE;			                          //使能USART2时钟
	
    //发  
		GPIO_Init.Pin = UARTx_Tx_PIN;			              //PA2 
		GPIO_Init.Mode = GPIO_MODE_AF_PP;		              //复用推挽输出
		GPIO_Init.Pull = GPIO_NOPULL;			                //不拉
		GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;            //低速
		HAL_GPIO_Init(UARTx_Tx_GPIO_PORT,&GPIO_Init);	  //初始化PA2

    //收
		GPIO_Init.Pin = UARTx_Rx_PIN;			              //PA3 
		GPIO_Init.Mode = GPIO_MODE_INPUT;	                //浮空输入
		HAL_GPIO_Init(UARTx_Rx_GPIO_PORT,&GPIO_Init);	  //初始化PA3

//#if EN_USART1_RX
		HAL_NVIC_EnableIRQ(UARTx_IRQn);				          //使能USART2中断通道
		HAL_NVIC_SetPriority(UARTx_IRQn,0,2);			      //抢占优先级0，子优先级2
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
  //重置外设
  UARTx_FORCE_RESET();
  UARTx_RELEASE_RESET();

  //失能管脚时钟
  HAL_GPIO_DeInit(UARTx_Tx_GPIO_PORT, UARTx_Tx_PIN);
  HAL_GPIO_DeInit(UARTx_Rx_GPIO_PORT, UARTx_Rx_PIN);

  //失能中断
  HAL_NVIC_DisableIRQ(UARTx_IRQn);
}
