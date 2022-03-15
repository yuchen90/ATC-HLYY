////////////////////////////////////////////////////////////////
/*
串口2初始化
*/
////////////////////////////////////////////////////////////////
#include "stm32f10x.h"
#include "common.h"
#include "data.h"


	void CAN_Send(u32 SID,unsigned char data1[8]);




void uart2_init(void)
{

	GPIO_InitTypeDef GPIO_InitStrue;
	USART_InitTypeDef USART_InitStrue;
	NVIC_InitTypeDef NVIC_InitStrue;

	
	// 外设使能时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	USART_DeInit(USART2);  //复位串口2 -> 可以没有
	
	// 初始化 串口对应IO口  TX-PA2  RX-PA3
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStrue);
	
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_3;
  GPIO_Init(GPIOA,&GPIO_InitStrue);
	
	// 初始化 串口模式状态
	USART_InitStrue.USART_BaudRate=4800; // 波特率
	USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None; // 硬件流控制
	USART_InitStrue.USART_Mode=USART_Mode_Tx|USART_Mode_Rx; // 发送 接收 模式都使用
	USART_InitStrue.USART_Parity=USART_Parity_No; // 没有奇偶校验
	USART_InitStrue.USART_StopBits=USART_StopBits_1; // 一位停止位
	USART_InitStrue.USART_WordLength=USART_WordLength_8b; // 每次发送数据宽度为8位
	USART_Init(USART2,&USART_InitStrue);
	
	USART_Cmd(USART2,ENABLE);//使能串口
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//开启接收中断
	
	// 初始化 中断优先级
	NVIC_InitStrue.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=2;
	
	NVIC_Init(&NVIC_InitStrue);

}

void  fputcU2(int ch)
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	USART_SendData(USART2, (uint8_t) ch);

	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
	{}

}


void USART2_IRQHandler(void)
{
	unsigned char chD;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		/* Read one byte from the receive data register */
		chD=USART_ReceiveData(USART2);//SUBF:数据缓冲器
	//	comdataSTR[];
		JSYReadbuff[JSYReadFg++]=chD;
	}

}


	uint8_t MDsenddata[8]={0x01,0x03,0x00,0x48,0x00,0x06,0x45,0xDe};
	//int vnamb;
	void sendMD()
	{
//		vnamb=(JSYReadbuff[3]<<8)+JSYReadbuff[4];
		for(int i=0;i<40;i++)
			JSYReadbuff[i]=0;
		
		JSYReadFg=0;
		for(int i=0;i<8;i++)
			fputcU2(MDsenddata[i]);
		
	}

	
uint16_t Voltage_R1_numb1,Voltage_R1_numb2;
uint16_t Voltage_R1_numb3,Voltage_R1_numb4;
uint8_t data12;
void checklamp()
{
	uint32_t SID;
	uint8_t data1[8];
	if(timerfg==100)
		CAN_R_LED(SOFF);
	if(timerfg==400)
		CAN_T_LED(SON);
	if(timerfg>=1200)//回码时间
	{
		if(JSYReadbuff[2]>4)
		{
			SID=0x0a;
			SID=SID<<3;
			SID+=0x80;
			SID+=Version;
			data1[7]=JSYReadbuff[3];
			data1[6]=JSYReadbuff[4];
			data1[5]=JSYReadbuff[5];
			data1[4]=JSYReadbuff[6];
			
		//	data1[3]=JSYReadbuff[9];
		//	data1[2]=JSYReadbuff[10];

		//	data1[1]=JSYReadbuff[11];
		//	data1[0]=JSYReadbuff[12];
			
			data1[3]=0;
			data1[2]=0;
			data1[1]=0;
			data1[0]=0;
			
			Voltage_R1_numb=Voltage_R2_numb+Voltage_R1_numb;
			Voltage_R1_numb=Voltage_R1_numb/2;
			if(Voltage_R1_numb<0x1000)//代表黄灯是否有电  bit0    1  有电
			{
					data1[0]=0;
					Voltage_R1_fg++;
					if(Voltage_R1_fg>4)
						Voltage_R1_fg=4;
			}
			else
			{
				data1[0]=1;
				Voltage_R1_fg=0;
			}
			Voltage_R1_numb1=Voltage_R1_numb;
			Voltage_R1_numb2=Voltage_R2_numb;
			Voltage_R1_numb3=Voltage_R3_numb+Voltage_R1_numb;
			Voltage_R1_numb4=Voltage_R4_numb+Voltage_R2_numb;
			
			Voltage_R1_numb=0;
			Voltage_R2_numb=0;
			Voltage_R3_numb=0;
			Voltage_R4_numb=0;
			
			if(Voltage_R1_fg<4)			//是否连续1秒无黄灯   bit1   1  
				data1[0]+=0x02;
			if(Y_FLASHorder==1)//表示电源板接管时检测到故障是否需要执行硬黄闪  bit2  1 需要黄闪
				data1[0]+=0x04;
			if(TakeOverorder==1)//表示主控板失效时电源板是否进行接管 bit3    1 需要接管
				data1[0]+=0x08;
			if(TakeOverNumbuse>0)//是否已经拥有接管方案  bit4    1 已经有接管信息
				data1[0]+=0x10;
			
				data12=data1[0];
	
			CAN_Send(SID,data1);
			
			CAN_T_LED(SOFF);

		}
		cheakfg2=0;

		if(cheakmdfg==0)
				sendMD();
	}

}