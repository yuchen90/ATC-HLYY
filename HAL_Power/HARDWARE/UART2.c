#include "main.h"
#include "declaration.h"

void UART_Error_Handler(void);

/**
  * @brief  USART2 句柄参数配置，以及外设使能，开启接收中断
  * @param  baudrate：串口通讯速率
  * @retval None
  */
void UART2_Init(uint32_t baudrate)
{
	POWER_UART2_Handle.Instance = USART2;									//USART2
	POWER_UART2_Handle.Init.BaudRate = baudrate;							//波特率
	POWER_UART2_Handle.Init.WordLength = UART_WORDLENGTH_8B;				//字长8bits
	POWER_UART2_Handle.Init.StopBits = UART_STOPBITS_1;						//一个停止位
	POWER_UART2_Handle.Init.Parity = UART_PARITY_NONE;						//无奇偶校验
	POWER_UART2_Handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;				//无硬件控制
	POWER_UART2_Handle.Init.Mode = UART_MODE_TX_RX;							//收发模式
	#if UART2_EN
	if (HAL_UART_Init(&POWER_UART2_Handle) != HAL_OK)						//使能UART2,HAL_UART_Init()会先调用MSP初始化函数
    	UART_Error_Handler();											
	#endif
}

/**
  * @brief  USART2 发送中断处理函数
  * @param  *huart：外设句柄地址
  * @retval None
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if (HAL_UART_Receive_DMA(&POWER_UART2_Handle,UART_Rx_Buff,UART2_RxDataSize) != HAL_OK)
    	UART_Error_Handler();
	// while (HAL_UART_GetState(&POWER_UART2_Handle) != HAL_UART_STATE_READY);
}

/**
  * @brief  USART2 接收中断处理函数
  * @param  *huart：外设句柄地址
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{	
	uint8_t i;

	if(huart->Instance == USART2)
	{
		for(i=0u;i<17;i++)
		{
			JSY_MK163_ReadBuff[i] = UART_Rx_Buff[i];
			JSY_MK163_ReadNum++;
		}	
	}
}

/**
  * @brief  通过串口发送读命令给JSY
  * @param  None
  * @retval None
  */
void JSY_DataRequest(void)
{
	if (HAL_UART_Transmit_DMA(&POWER_UART2_Handle,UART_Send_Buff,UART2_TxDataSize) != HAL_OK)
    	UART_Error_Handler();
// while (HAL_UART_GetState(&POWER_UART2_Handle) != HAL_UART_STATE_READY);
}

/**
  * @brief  UART初始化，错误CAN_Tx_LED常亮
  * @param  None
  * @retval None
  */
void UART_Error_Handler(void)
{
	while(1)
	{
    	CAN_Tx_LED=LED_ON;
	}
}
