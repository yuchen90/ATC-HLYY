#include "main.h"
#include "declaration.h"

UART_HandleTypeDef UART2_Handle;
uint8_t UART_Rx_Buff[UART_RxDataSize];

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
	HAL_UART_Init(&UART2_Handle);									//使能UART2,HAL_UART_Init()会先调用MSP初始化函数

	HAL_UART_Receive_IT(&UART2_Handle,UART_Rx_Buff,UART_RxDataSize);			//这个函数的第2个和第3个参数可以修改，可以把第二个接收缓存直接改
																	//为全局变量JSY_MK163_ReadBuff，第三个变量改为JSY收到查询信息后返回的字节数
																	//现在是收到一个字节就调用一次中断，修改后是完成接收规定字节数后才调用中断
	#endif
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	//处理接收到的1字节数据
	if(huart->Instance == USART2)									//如果是USART2
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
