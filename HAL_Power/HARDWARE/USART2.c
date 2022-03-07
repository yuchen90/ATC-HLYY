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
	HAL_UART_Init(&USART2_Handle);									//使能UART2,HAL_UART_Init()会先调用MSP初始化函数

	HAL_UART_Receive_IT(&USART2_Handle,UART_Rx_Buff,1u);			//这个函数的第2个和第3个参数可以修改，可以把第二个接收缓存直接改
																	//为全局变量JSY_MK163_ReadBuff，第三个变量改为JSY收到查询信息后返回的字节数
																	//现在是收到一个字节就调用一次中断，修改后是完成接收规定字节数后才调用中断
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	
	uint32_t timeout;
	timeout=0;
	while (HAL_UART_GetState(&USART2_Handle) != HAL_UART_STATE_READY)//等待就绪
	{
		timeout++;////超时处理
    	if(timeout>HAL_MAX_DELAY) break;		
	}
    
	
	timeout=0;
	while(HAL_UART_Receive_IT(&USART2_Handle,UART_Rx_Buff,1u) != HAL_OK)//一次处理完成之后，重新开启中断并设置为接收1个字节后中断
	{
		timeout++; //超时处理
		if(timeout>HAL_MAX_DELAY) break;	
	}
}