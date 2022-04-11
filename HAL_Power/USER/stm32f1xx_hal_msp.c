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
  * 定时器底册驱动，开启时钟，设置中断优先级
  * @retval None
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
  if(htim->Instance == TIM2)                          //确认开启时钟为TIM2
	{
	    TIM2_CLK_ENABLE();                                //使能TIM2时钟
		HAL_NVIC_SetPriority(TIM2_IRQn,1u,0u);            //设置中断优先级，抢占优先级3，子优先级3
		HAL_NVIC_EnableIRQ(TIM2_IRQn);                    //开启ITM2中断   
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
  GPIO_InitTypeDef GPIO_Init={0u};

  CAN1_CLK_ENABLE();
  CAN1_GPIO_CLK_ENABLE();

  //Rx
  GPIO_Init.Pin=CAN1_Rx_PIN;
  GPIO_Init.Mode=GPIO_MODE_INPUT;
  GPIO_Init.Pull=GPIO_PULLUP;
  HAL_GPIO_Init(CAN1_Rx_GPIO_PORT,&GPIO_Init);

  //Tx
  GPIO_Init.Pin=CAN1_Tx_PIN;
  GPIO_Init.Mode=GPIO_MODE_AF_PP;
  GPIO_Init.Speed=GPIO_SPEED_FREQ_HIGH;                       //10M带宽 信号速度为0.6MHz
  HAL_GPIO_Init(CAN1_Tx_GPIO_PORT,&GPIO_Init); 

  //CAN1 Rx Interrupt Init
  HAL_NVIC_SetPriority(CAN1_Rx_EXID_IRQn,0u,0u);              //抢占优先级：
  HAL_NVIC_EnableIRQ(CAN1_Rx_EXID_IRQn); 

  HAL_NVIC_SetPriority(CAN1_Rx_SID_IRQn,0u,1u);               //抢占优先级：
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
  // 外设时钟关闭
  __HAL_RCC_CAN1_CLK_DISABLE();

  // 失能外设时钟
  HAL_GPIO_DeInit(CAN1_Tx_GPIO_PORT, CAN1_Tx_PIN|CAN1_Rx_PIN);

  // 失能中断
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

	if(huart->Instance == USART2)                                       //如果是串口2，进行串口2 MSP初始化
	{
	  UART2_GPIO_CLK_ENABLE();			                                    //使能GPIOA时钟
	  UART2_CLK_ENABLE;			                                            //使能USART2时钟
    UART2_DMA_CLK_ENABLE();
	
    //发  
		GPIO_Init.Pin=UART2_Tx_PIN;			                                  //PA2 
		GPIO_Init.Mode=GPIO_MODE_AF_PP;		                                //复用推挽输出
		GPIO_Init.Speed=GPIO_SPEED_FREQ_HIGH;                             //高速
		HAL_GPIO_Init(UART2_Tx_GPIO_PORT,&GPIO_Init);	                    //初始化PA2

    //收
		GPIO_Init.Pin=UART2_Rx_PIN;			                                  //PA3 
		GPIO_Init.Mode=GPIO_MODE_INPUT;	                                  //输入
    GPIO_Init.Pull=GPIO_NOPULL;                                       //浮空
		HAL_GPIO_Init(UART2_Rx_GPIO_PORT,&GPIO_Init);	                    //初始化PA

	  //Rx
	  UART2Rx_DMA_Handle.Instance=DMA1_Channel6;							          //通道选择
	  UART2Rx_DMA_Handle.Init.Direction=DMA_PERIPH_TO_MEMORY;			      //外设到存储器
	  UART2Rx_DMA_Handle.Init.PeriphInc=DMA_PINC_DISABLE;					      //外设非增量模式
	  UART2Rx_DMA_Handle.Init.MemInc=DMA_MINC_ENABLE;						        //存储器增量模式
	  UART2Rx_DMA_Handle.Init.PeriphDataAlignment=DMA_PDATAALIGN_BYTE;	//外设数据长度:8位
	  UART2Rx_DMA_Handle.Init.MemDataAlignment=DMA_MDATAALIGN_BYTE;		  //存储器数据长度:8位
	  UART2Rx_DMA_Handle.Init.Mode=DMA_NORMAL;                          //外设普通模式
	  UART2Rx_DMA_Handle.Init.Priority=DMA_PRIORITY_HIGH;               //高等优先级;
	
	  HAL_DMA_Init(&UART2Rx_DMA_Handle);

	  /* Associate the initialized DMA handle to the UART handle */
	  __HAL_LINKDMA(&POWER_UART2_Handle, hdmarx, UART2Rx_DMA_Handle);

	  //Tx
	  UART2Tx_DMA_Handle.Instance=DMA1_Channel7;							          //通道选择
	  UART2Tx_DMA_Handle.Init.Direction=DMA_MEMORY_TO_PERIPH;				    //存储器到外设
	  UART2Tx_DMA_Handle.Init.PeriphInc=DMA_PINC_DISABLE;					      //外设非增量模式
	  UART2Tx_DMA_Handle.Init.MemInc=DMA_MINC_ENABLE;						        //存储器增量模式
	  UART2Tx_DMA_Handle.Init.PeriphDataAlignment=DMA_PDATAALIGN_BYTE;	//外设数据长度:8位
	  UART2Tx_DMA_Handle.Init.MemDataAlignment=DMA_MDATAALIGN_BYTE;		  //存储器数据长度:8位
	  UART2Tx_DMA_Handle.Init.Mode=DMA_NORMAL;                          //外设普通模式
	  UART2Tx_DMA_Handle.Init.Priority=DMA_PRIORITY_MEDIUM;             //中等优先级;
    
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
		HAL_NVIC_SetPriority(UART2_IRQn,0,1);			                        //抢占优先级0，子优先级2
    HAL_NVIC_EnableIRQ(UART2_IRQn);				                            //使能USART2中断通道
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
  //关闭外设时钟
  __HAL_RCC_USART2_CLK_DISABLE();
  
  //失能管脚时钟
  HAL_GPIO_DeInit(UART2_Tx_GPIO_PORT, UART2_Tx_PIN|UART2_Rx_PIN);

  HAL_DMA_DeInit(&UART2Rx_DMA_Handle);
  HAL_DMA_DeInit(&UART2Tx_DMA_Handle);
  //失能中断
  HAL_NVIC_DisableIRQ(UART2_DMA_Tx_IRQn);
  HAL_NVIC_DisableIRQ(UART2_DMA_Rx_IRQn);
}
