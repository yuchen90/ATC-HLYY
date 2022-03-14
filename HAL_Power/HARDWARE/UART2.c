#include "main.h"
#include "declaration.h"

UART_HandleTypeDef UART2_Handle;
uint8_t UART_Rx_Buff[UART_RxDataSize];

/**
  * @brief  USART2 句柄参数配置，以及外设使能，开启接收中断
  * @param  baudrate：串口通讯速率
  * @retval None
  */
void UART_Init(uint32_t baudrate)
{
	UART2_Handle.Instance = UARTx;									//USART2
	UART2_Handle.Init.BaudRate = baudrate;							//波特率
	UART2_Handle.Init.WordLength = UART_WORDLENGTH_8B;				//字长8bits
	UART2_Handle.Init.StopBits = UART_STOPBITS_1;					//一个停止位
	UART2_Handle.Init.Parity = UART_PARITY_NONE;					//无奇偶校验
	UART2_Handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;				//无硬件控制
	UART2_Handle.Init.Mode = UART_MODE_TX_RX;						//收发模式
	#if UART2_EN
	if (HAL_UART_Init(&UART2_Handle) != HAL_OK)						//使能UART2,HAL_UART_Init()会先调用MSP初始化函数
	{
    	Error_Handler();											
	}
	#endif
}

/**
  * @brief  USART2 接收中断处理函数
  * @param  *huart：外设句柄地址
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	//处理接收到的所有数据
	if(huart->Instance == USART2)									//如果是USART2
	{
		JSY_MK163_ReadBuff[JSY_MK163_ReadNum++] = UART_Rx_Buff[0];
	}
	while(HAL_UART_Receive_IT(&UART2_Handle,UART_Rx_Buff,UART_RxDataSize) != HAL_OK)
	e++;
}

// void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
// {
// 	while(HAL_UART_Receive_IT(&UART2_Handle,UART_Rx_Buff,UART_RxDataSize) != HAL_OK);
// }

/**
  * @brief  通过串口发送读命令给JSY
  * @param  None
  * @retval None
  */
void JSY_DataRequest(void)
{
	r = HAL_UART_GetState(&UART2_Handle);
	HAL_UART_Transmit(&UART2_Handle,SendBuff,8u,50);
	HAL_UART_Receive_IT(&UART2_Handle,UART_Rx_Buff,UART_RxDataSize);
}
