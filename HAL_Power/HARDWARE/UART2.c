#include "main.h"
#include "declaration.h"

UART_HandleTypeDef UART2_Handle;
uint8_t UART_Rx_Buff[UART_RxDataSize];

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
	HAL_UART_Init(&UART2_Handle);									//ʹ��UART2,HAL_UART_Init()���ȵ���MSP��ʼ������

	HAL_UART_Receive_IT(&UART2_Handle,UART_Rx_Buff,UART_RxDataSize);			//��������ĵ�2���͵�3�����������޸ģ����԰ѵڶ������ջ���ֱ�Ӹ�
																	//Ϊȫ�ֱ���JSY_MK163_ReadBuff��������������ΪJSY�յ���ѯ��Ϣ�󷵻ص��ֽ���
																	//�������յ�һ���ֽھ͵���һ���жϣ��޸ĺ�����ɽ��չ涨�ֽ�����ŵ����ж�
	#endif
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	//������յ���1�ֽ�����
	if(huart->Instance == USART2)									//�����USART2
	{
		JSY_MK163_ReadBuff[JSY_MK163_ReadNum++] = UART_Rx_Buff[0];
	}
}

void JSY_DataRequest(void)
{
	uint8_t SendBuff[8] = {0x01,0x03,0x00,0x48,0x00,0x06,0x45,0xDE};
	if(HAL_UART_GetState(&UART2_Handle) == HAL_UART_STATE_READY)
	{
		HAL_UART_Transmit_IT(&UART2_Handle,SendBuff,8u);
	}
}
