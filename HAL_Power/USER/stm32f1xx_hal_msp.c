#include "main.h"

/*------------------------------------------------------------------------------------------------------------------------------------
TIM
------------------------------------------------------------------------------------------------------------------------------------*/

/**
  * @brief TIM MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  * @param htim: TIM handle pointer
  * ��ʱ���ײ�����������ʱ�ӣ������ж����ȼ�
  * @retval None
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
  if(htim->Instance==TIMx)                         //ȷ�Ͽ���ʱ��ΪTIM2
	{
	  TIMx_CLK_ENABLE();                             //ʹ��TIM2ʱ��
		HAL_NVIC_SetPriority(TIMx_IRQn,3u,3u);         //�����ж����ȼ�����ռ���ȼ�3�������ȼ�3
		HAL_NVIC_EnableIRQ(TIMx_IRQn);                 //����ITM2�ж�   
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
  GPIO_Init.Speed = GPIO_SPEED_FREQ_MEDIUM;         //10M���� �ź��ٶ�Ϊ0.6MHz
  GPIO_Init.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(CANx_TX_GPIO_PORT,&GPIO_Init); 

  //CAN1 Rx Interrupt Init
  HAL_NVIC_SetPriority(CANx_RX_IRQn,2u,2u);         //��ռ���ȼ���2
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
  // ��������
  CANx_FORCE_RESET();
  CANx_RELEASE_RESET();

  // ʧ������ʱ��
  HAL_GPIO_DeInit(CANx_TX_GPIO_PORT, CANx_TX_PIN);
  HAL_GPIO_DeInit(CANx_RX_GPIO_PORT, CANx_RX_PIN);

  // ʧ���ж�
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

	if(huart->Instance==UARTx)                         //����Ǵ���2�����д���2 MSP��ʼ��
	{
		UARTx_GPIO_CLK_ENABLE();			                    //ʹ��GPIOAʱ��
		UARTx_CLK_ENABLE;			                          //ʹ��USART2ʱ��
	
    //��  
		GPIO_Init.Pin = UARTx_Tx_PIN;			              //PA2 
		GPIO_Init.Mode = GPIO_MODE_AF_PP;		              //�����������
		GPIO_Init.Pull = GPIO_NOPULL;			                //����
		GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;            //����
		HAL_GPIO_Init(UARTx_Tx_GPIO_PORT,&GPIO_Init);	  //��ʼ��PA2

    //��
		GPIO_Init.Pin = UARTx_Rx_PIN;			              //PA3 
		GPIO_Init.Mode = GPIO_MODE_INPUT;	                //��������
		HAL_GPIO_Init(UARTx_Rx_GPIO_PORT,&GPIO_Init);	  //��ʼ��PA3

//#if EN_USART1_RX
		HAL_NVIC_EnableIRQ(UARTx_IRQn);				          //ʹ��USART2�ж�ͨ��
		HAL_NVIC_SetPriority(UARTx_IRQn,0,2);			      //��ռ���ȼ�0�������ȼ�2
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
  //��������
  UARTx_FORCE_RESET();
  UARTx_RELEASE_RESET();

  //ʧ�ܹܽ�ʱ��
  HAL_GPIO_DeInit(UARTx_Tx_GPIO_PORT, UARTx_Tx_PIN);
  HAL_GPIO_DeInit(UARTx_Rx_GPIO_PORT, UARTx_Rx_PIN);

  //ʧ���ж�
  HAL_NVIC_DisableIRQ(UARTx_IRQn);
}
