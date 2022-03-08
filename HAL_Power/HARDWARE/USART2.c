#include "main.h"
#include "declaration.h"

UART_HandleTypeDef USART2_Handle;
uint8_t UART_Rx_Buff[USART_RxDataSize];

void USART_Init(uint32_t baudrate)
{
	USART2_Handle.Instance = USARTx;								//USART2
	USART2_Handle.Init.BaudRate = baudrate;							//������
	USART2_Handle.Init.WordLength = UART_WORDLENGTH_8B;				//�ֳ�8bits
	USART2_Handle.Init.StopBits = UART_STOPBITS_1;					//һ��ֹͣλ
	USART2_Handle.Init.Parity = UART_PARITY_NONE;					//����żУ��
	USART2_Handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;				//��Ӳ������
	USART2_Handle.Init.Mode = UART_MODE_TX_RX;						//�շ�ģʽ
	#if USART2_EN
	HAL_UART_Init(&USART2_Handle);									//ʹ��UART2,HAL_UART_Init()���ȵ���MSP��ʼ������

	HAL_UART_Receive_IT(&USART2_Handle,UART_Rx_Buff,USART_RxDataSize);			//��������ĵ�2���͵�3�����������޸ģ����԰ѵڶ������ջ���ֱ�Ӹ�
																	//Ϊȫ�ֱ���JSY_MK163_ReadBuff��������������ΪJSY�յ���ѯ��Ϣ�󷵻ص��ֽ���
																	//�������յ�һ���ֽھ͵���һ���жϣ��޸ĺ�����ɽ��չ涨�ֽ�����ŵ����ж�
	#endif
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	//������յ���1�ֽ�����
	if(huart->Instance == USART2)									//�����USART2
	{
		JSY_MK163_ReadBuff[JSY_MK163_ReadNum] = UART_Rx_Buff[0];
		JSY_MK163_ReadNum++;
		if(JSY_MK163_ReadNum == USART_RxBuffSize)
		{}
	}
}

void Clear_UART_Rx_Buff(void)
{
	uint8_t i;
	for(i=0;i<40;i++)
		JSY_MK163_ReadBuff[i] = 0u;
}
