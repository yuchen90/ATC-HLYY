#include "main.h"
#include "declaration.h"

void UART_Error_Handler(void);

/**
  * @brief  USART2 ����������ã��Լ�����ʹ�ܣ����������ж�
  * @param  baudrate������ͨѶ����
  * @retval None
  */
void UART2_Init(uint32_t baudrate)
{
	POWER_UART2_Handle.Instance = USART2;									//USART2
	POWER_UART2_Handle.Init.BaudRate = baudrate;							//������
	POWER_UART2_Handle.Init.WordLength = UART_WORDLENGTH_8B;				//�ֳ�8bits
	POWER_UART2_Handle.Init.StopBits = UART_STOPBITS_1;						//һ��ֹͣλ
	POWER_UART2_Handle.Init.Parity = UART_PARITY_NONE;						//����żУ��
	POWER_UART2_Handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;				//��Ӳ������
	POWER_UART2_Handle.Init.Mode = UART_MODE_TX_RX;							//�շ�ģʽ
	#if UART2_EN
	if (HAL_UART_Init(&POWER_UART2_Handle) != HAL_OK)						//ʹ��UART2,HAL_UART_Init()���ȵ���MSP��ʼ������
    	UART_Error_Handler();											
	#endif
}

/**
  * @brief  USART2 �����жϴ�����
  * @param  *huart����������ַ
  * @retval None
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if (HAL_UART_Receive_DMA(&POWER_UART2_Handle,UART_Rx_Buff,UART2_RxDataSize) != HAL_OK)
    	UART_Error_Handler();
	// while (HAL_UART_GetState(&POWER_UART2_Handle) != HAL_UART_STATE_READY);
}

/**
  * @brief  USART2 �����жϴ�����
  * @param  *huart����������ַ
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
  * @brief  ͨ�����ڷ��Ͷ������JSY
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
  * @brief  UART��ʼ��������CAN_Tx_LED����
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
