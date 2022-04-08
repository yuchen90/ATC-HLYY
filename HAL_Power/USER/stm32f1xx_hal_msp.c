#include "main.h"
#include "stm32f1xx_hal.h"
#include "declaration.h"

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
  if(htim->Instance == TIM2)                          //ȷ�Ͽ���ʱ��ΪTIM2
	{
	  TIMx_CLK_ENABLE();                                //ʹ��TIM2ʱ��
		HAL_NVIC_SetPriority(TIM2_IRQn,1u,0u);            //�����ж����ȼ�����ռ���ȼ�3�������ȼ�3
		HAL_NVIC_EnableIRQ(TIM2_IRQn);                    //����ITM2�ж�   
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
  if(htim->Instance == TIM2)
  {
    __HAL_RCC_TIM2_FORCE_RESET();
    __HAL_RCC_TIM2_RELEASE_RESET();
    //�ر�TIM2ʱ��
    __HAL_RCC_TIM2_CLK_DISABLE();
    //�ر�TIM2�ж�
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
  GPIO_InitTypeDef GPIO_Init={0u};

  CANx_CLK_ENABLE();
  CANx_GPIO_CLK_ENABLE();

  //Rx
  GPIO_Init.Pin=CAN1_Rx_PIN;
  GPIO_Init.Mode=GPIO_MODE_INPUT;
  GPIO_Init.Pull=GPIO_PULLUP;
  HAL_GPIO_Init(CAN1_Rx_GPIO_PORT,&GPIO_Init);

  //Tx
  GPIO_Init.Pin=CAN1_Tx_PIN;
  GPIO_Init.Mode=GPIO_MODE_AF_PP;
  GPIO_Init.Speed=GPIO_SPEED_FREQ_HIGH;                       //10M���� �ź��ٶ�Ϊ0.6MHz
  HAL_GPIO_Init(CAN1_Tx_GPIO_PORT,&GPIO_Init); 

  //CAN1 Rx Interrupt Init
  HAL_NVIC_SetPriority(CAN1_Rx_EXID_IRQn,0u,0u);              //��ռ���ȼ���
  HAL_NVIC_EnableIRQ(CAN1_Rx_EXID_IRQn); 

  HAL_NVIC_SetPriority(CAN1_Rx_SID_IRQn,0u,1u);               //��ռ���ȼ���
  HAL_NVIC_EnableIRQ(CAN1_Rx_SID_IRQn); 
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
  __HAL_RCC_CAN1_FORCE_RESET();
  __HAL_RCC_CAN1_RELEASE_RESET();
  // ����ʱ�ӹر�
  __HAL_RCC_CAN1_CLK_DISABLE();

  // ʧ������ʱ��
  HAL_GPIO_DeInit(CAN1_Tx_GPIO_PORT, CAN1_Tx_PIN|CAN1_Rx_PIN);

  // ʧ���ж�
  HAL_NVIC_DisableIRQ(CAN1_Rx_SID_IRQn);
  HAL_NVIC_DisableIRQ(CAN1_Rx_EXID_IRQn);
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
  GPIO_InitTypeDef GPIO_Init={0u};

	if(huart->Instance == USART2)                                       //����Ǵ���2�����д���2 MSP��ʼ��
	{
	  UART2_GPIO_CLK_ENABLE();			                                    //ʹ��GPIOAʱ��
	  UART2_CLK_ENABLE;			                                            //ʹ��USART2ʱ��
    UART2_DMA_CLK_ENABLE();
	
    //��  
		GPIO_Init.Pin=UART2_Tx_PIN;			                                  //PA2 
		GPIO_Init.Mode=GPIO_MODE_AF_PP;		                                //�����������
		GPIO_Init.Speed=GPIO_SPEED_FREQ_HIGH;                             //����
		HAL_GPIO_Init(UART2_Tx_GPIO_PORT,&GPIO_Init);	                    //��ʼ��PA2

    //��
		GPIO_Init.Pin=UART2_Rx_PIN;			                                  //PA3 
		GPIO_Init.Mode=GPIO_MODE_INPUT;	                                  //����
    GPIO_Init.Pull=GPIO_NOPULL;                                       //����
		HAL_GPIO_Init(UART2_Rx_GPIO_PORT,&GPIO_Init);	                    //��ʼ��PA

	  //Rx
	  UART2Rx_DMA_Handle.Instance=DMA1_Channel6;							          //ͨ��ѡ��
	  UART2Rx_DMA_Handle.Init.Direction=DMA_PERIPH_TO_MEMORY;			      //���赽�洢��
	  UART2Rx_DMA_Handle.Init.PeriphInc=DMA_PINC_DISABLE;					      //���������ģʽ
	  UART2Rx_DMA_Handle.Init.MemInc=DMA_MINC_ENABLE;						        //�洢������ģʽ
	  UART2Rx_DMA_Handle.Init.PeriphDataAlignment=DMA_PDATAALIGN_BYTE;	//�������ݳ���:8λ
	  UART2Rx_DMA_Handle.Init.MemDataAlignment=DMA_MDATAALIGN_BYTE;		  //�洢�����ݳ���:8λ
	  UART2Rx_DMA_Handle.Init.Mode=DMA_NORMAL;                          //������ͨģʽ
	  UART2Rx_DMA_Handle.Init.Priority=DMA_PRIORITY_HIGH;               //�ߵ����ȼ�;
	
	  HAL_DMA_Init(&UART2Rx_DMA_Handle);

	  /* Associate the initialized DMA handle to the UART handle */
	  __HAL_LINKDMA(&POWER_UART2_Handle, hdmarx, UART2Rx_DMA_Handle);

	  //Tx
	  UART2Tx_DMA_Handle.Instance=DMA1_Channel7;							          //ͨ��ѡ��
	  UART2Tx_DMA_Handle.Init.Direction=DMA_MEMORY_TO_PERIPH;				    //�洢��������
	  UART2Tx_DMA_Handle.Init.PeriphInc=DMA_PINC_DISABLE;					      //���������ģʽ
	  UART2Tx_DMA_Handle.Init.MemInc=DMA_MINC_ENABLE;						        //�洢������ģʽ
	  UART2Tx_DMA_Handle.Init.PeriphDataAlignment=DMA_PDATAALIGN_BYTE;	//�������ݳ���:8λ
	  UART2Tx_DMA_Handle.Init.MemDataAlignment=DMA_MDATAALIGN_BYTE;		  //�洢�����ݳ���:8λ
	  UART2Tx_DMA_Handle.Init.Mode=DMA_NORMAL;                          //������ͨģʽ
	  UART2Tx_DMA_Handle.Init.Priority=DMA_PRIORITY_MEDIUM;             //�е����ȼ�;
    
    HAL_DMA_Init(&UART2Tx_DMA_Handle);

	  /* Associate the initialized DMA handle to the UART handle */
	  __HAL_LINKDMA(&POWER_UART2_Handle, hdmatx, UART2Tx_DMA_Handle);

    /* NVIC configuration for DMA transfer complete interrupt (USARTx_TX) */
    HAL_NVIC_SetPriority(UART2_DMA_Tx_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(UART2_DMA_Tx_IRQn);

    /* NVIC configuration for DMA transfer complete interrupt (USARTx_RX) */
    HAL_NVIC_SetPriority(UART2_DMA_Rx_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(UART2_DMA_Rx_IRQn);

    //#if EN_USART1_RX
		HAL_NVIC_SetPriority(UART2_IRQn,0,1);			                        //��ռ���ȼ�0�������ȼ�2
    HAL_NVIC_EnableIRQ(UART2_IRQn);				                            //ʹ��USART2�ж�ͨ��
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
  __HAL_RCC_USART2_FORCE_RESET();
  __HAL_RCC_USART2_RELEASE_RESET();
  //�ر�����ʱ��
  __HAL_RCC_USART2_CLK_DISABLE();
  
  //ʧ�ܹܽ�ʱ��
  HAL_GPIO_DeInit(UART2_Tx_GPIO_PORT, UART2_Tx_PIN|UART2_Rx_PIN);

  HAL_DMA_DeInit(&UART2Rx_DMA_Handle);
  HAL_DMA_DeInit(&UART2Tx_DMA_Handle);
  //ʧ���ж�
  HAL_NVIC_DisableIRQ(UART2_DMA_Tx_IRQn);
  HAL_NVIC_DisableIRQ(UART2_DMA_Rx_IRQn);
}
