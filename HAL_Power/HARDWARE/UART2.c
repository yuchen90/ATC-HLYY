#include "main.h"
#include "declaration.h"

UART_HandleTypeDef UART2_Handle;
uint8_t UART_Rx_Buff[UART_RxDataSize];
HAL_UART_StateTypeDef HAL_UART_GetRxState(UART_HandleTypeDef *huart);
HAL_UART_StateTypeDef HAL_UART_GetgState(UART_HandleTypeDef *huart);

/**
  * @brief  USART2 ����������ã��Լ�����ʹ�ܣ����������ж�
  * @param  baudrate������ͨѶ����
  * @retval None
  */
void UART_Init(uint32_t baudrate)
{
	UART2_Handle.Instance = UARTx;									//USART2
	UART2_Handle.Init.BaudRate = baudrate;							//������
	UART2_Handle.Init.WordLength = UART_WORDLENGTH_8B;				//�ֳ�8bits
	UART2_Handle.Init.StopBits = UART_STOPBITS_1;					//һ��ֹͣλ
	UART2_Handle.Init.Parity = UART_PARITY_NONE;					//����żУ��
	UART2_Handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;				//��Ӳ������
	UART2_Handle.Init.Mode = UART_MODE_TX_RX;						//�շ�ģʽ
	#if UART2_EN
	if (HAL_UART_Init(&UART2_Handle) != HAL_OK)						//ʹ��UART2,HAL_UART_Init()���ȵ���MSP��ʼ������
	{
    	Error_Handler();											
	}
	#endif
}

/**
  * @brief  USART2 �����жϴ�����
  * @param  *huart����������ַ
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{	
	int i;
	//������յ�����������
	// if(huart->Instance == USART2)									//�����USART2
	// {
	// 	JSY_MK163_ReadBuff[JSY_MK163_ReadNum++] = UART_Rx_Buff[0];
	// }
	// while(HAL_UART_Receive_IT(&UART2_Handle,UART_Rx_Buff,UART_RxDataSize) != HAL_OK)
	// e++;
	if(huart->Instance == USART2)
	{
		for(i=0;i<17;i++)
		{
			JSY_MK163_ReadBuff[i] = UART_Rx_Buff[i];
			JSY_MK163_ReadNum++;
		}	
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	HAL_UART_Receive_IT(&UART2_Handle,UART_Rx_Buff,UART_RxDataSize);
}

/**
  * @brief  ͨ�����ڷ��Ͷ������JSY
  * @param  None
  * @retval None
  */
void JSY_DataRequest(void)
{
	HAL_UART_Transmit_IT(&UART2_Handle,SendBuff,8u);
	t++;
}


//�������������ǰ�HAL�⺯��HAL_UART_GetState������ֿ���ʹ��

/**
  * @brief  ��ѯ����gState������
  * @param  huart ���ھ����ַ
  * @retval gState
  */
HAL_UART_StateTypeDef HAL_UART_GetgState(UART_HandleTypeDef *huart)
{
  uint32_t temp1 = 0x00U;
  temp1 = huart->gState;

  return (HAL_UART_StateTypeDef)(temp1);
}

/**
  * @brief  ��ѯ����RxState���գ�
  * @param  huart ���ھ����ַ
  * @retval RxState
  */
HAL_UART_StateTypeDef HAL_UART_GetRxState(UART_HandleTypeDef *huart)
{
  uint32_t temp2 = 0x00U;
  temp2 = huart->RxState;

  return (HAL_UART_StateTypeDef)(temp2);
}


