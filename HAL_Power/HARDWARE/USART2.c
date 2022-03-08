#include "main.h"
#include "declaration.h"

UART_HandleTypeDef USART2_Handle;
uint8_t UART_Rx_Buff[USART_RxDataSize];

void USART_Init(uint32_t baudrate)
{
	USART2_Handle.Instance = USARTx;								//USART2
	USART2_Handle.Init.BaudRate = baudrate;							//波特率
	USART2_Handle.Init.WordLength = UART_WORDLENGTH_8B;				//字长8bits
	USART2_Handle.Init.StopBits = UART_STOPBITS_1;					//一个停止位
	USART2_Handle.Init.Parity = UART_PARITY_NONE;					//无奇偶校验
	USART2_Handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;				//无硬件控制
	USART2_Handle.Init.Mode = UART_MODE_TX_RX;						//收发模式
	#if USART2_EN
	HAL_UART_Init(&USART2_Handle);									//使能UART2,HAL_UART_Init()会先调用MSP初始化函数

	HAL_UART_Receive_IT(&USART2_Handle,UART_Rx_Buff,USART_RxDataSize);			//这个函数的第2个和第3个参数可以修改，可以把第二个接收缓存直接改
																	//为全局变量JSY_MK163_ReadBuff，第三个变量改为JSY收到查询信息后返回的字节数
																	//现在是收到一个字节就调用一次中断，修改后是完成接收规定字节数后才调用中断
	#endif
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	//处理接收到的1字节数据
	if(huart->Instance == USART2)									//如果是USART2
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
