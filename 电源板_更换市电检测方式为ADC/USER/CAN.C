////////////////////////////////////////////////////////////////
/*
CAN 通讯
*/
////////////////////////////////////////////////////////////////
#include "stm32f10x.h"
#include "common.h"
#include "data.h"


	void  init_can()	
	{
			NVIC_InitTypeDef NVIC_InitStructure;
			GPIO_InitTypeDef GPIO_InitStructure;
		
			CAN_InitTypeDef		CAN_InitStructure;
			CAN_FilterInitTypeDef	CAN_FilterInitStructure;
		
		
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);//CAN口时钟使能
		
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//I/O口时钟使能
		
		/* ConfigureCAN   pin:RX  PA11  */
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		/* Configure CAN pin: TX PA12*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,  &GPIO_InitStructure);
		
	//	GPIO_PinRemapConfig(GPIO_Remap2_CAN1 , ENABLE);
		
		/* CAN register?init */
		CAN_DeInit(CAN1);
		CAN_StructInit(&CAN_InitStructure);
		/* CAN cell init */
		CAN_InitStructure.CAN_TTCM=DISABLE;		//禁止时间触发通信模式
		CAN_InitStructure.CAN_ABOM=DISABLE;
		CAN_InitStructure.CAN_AWUM=DISABLE;		//睡眠模式通过清除sleep位来唤醒
		CAN_InitStructure.CAN_NART=DISABLE;		//ENABLE;报文自动重传
		CAN_InitStructure.CAN_RFLM=DISABLE;		//接收溢出时，FIFO未锁定 
		CAN_InitStructure.CAN_TXFP=DISABLE;		//发送的优先级由标示符的大小决定
		CAN_InitStructure.CAN_Mode=CAN_Mode_Normal;		//CAN_Mode_LoopBack;//
		
		//波特率 = (频率x4.5)/(CAN_BS1+CAN_BS2+1)/CAN_Prescaler
		//采样点  smp = (1+CAN_BS1)/(1+CAN_BS1+CAN_BS2)
		CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;		//SJW=0		//波特率计算，PCLK1=36MHZ,CAN波特率=36MHZ/(2+1)*(15+6+3)=500Kbs
		CAN_InitStructure.CAN_BS1=CAN_BS1_2tq;		//TS1=15		//波特率计算，PCLK1=36MHZ,CAN波特率=PCLK1/(BRP+1)*(TS1+TS2+3)
		CAN_InitStructure.CAN_BS2=CAN_BS2_2tq;		//TS2=6
		
		CAN_InitStructure.CAN_Prescaler=12;		//BRP=2????9/?45=50K/   4M    60=50K   50=60K   30=100K   24=125K  100
		
		CAN_Init(CAN1,&CAN_InitStructure);
		/*?CAN?filter?init?*/
		CAN_FilterInitStructure.CAN_FilterNumber=0;		//第1组过滤器
		CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;//屏蔽位模式
		CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;		//32位
		
		CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;
		CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
		CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;
		CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
		
		CAN_FilterInitStructure.CAN_FilterFIFOAssignment=0;//第一组过滤器指向FIFO0
		CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;
		CAN_FilterInit(&CAN_FilterInitStructure);
		/*?Enable?CAN?RX0?interrupt?IRQ?channel*/
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		//中断优先级组选择0组使用
		NVIC_InitStructure.NVIC_IRQChannel=USB_LP_CAN1_RX0_IRQn;		//USB_HP_CAN1_TX_IRQn 接收中断使能
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //抢占优先级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;//响应优先级
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		/* CAN? FIFO0 message pending interrupt enable */
		CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);//使能过滤器中断
	}
	
	
	unsigned char Can_Flag;
	
	
	void CAN_Send(u32 SID,unsigned char data1[8])		//CAN 发送 一标准帧数据 
	{
		CanTxMsg TxMessage;
		CanRxMsg RxMessage;
		uint16_t i;
		unsigned char TransmitMailbox;
		Can_Flag = 0;
		/* transmit 1 message */
		
		TxMessage.StdId=SID;//0x101;		//CanID;//0x00; ID标示符 // 
	//	TxMessage.ExtId=SID;					//  扩展标识符
		
		TxMessage.RTR=CAN_RTR_DATA;		//SRS	选择数据帧
		TxMessage.IDE=CAN_ID_STD;		//;// /选择标准帧   CAN_ID_STD           选择扩展帧  CAN_ID_EXT
		
		TxMessage.DLC=8;
		for(int i=0;i<8;i++)
			TxMessage.Data[i]=data1[i];		//data1;
		
		i=0;		
		do{
			TransmitMailbox  = CAN_Transmit(CAN1,&TxMessage);
			i++;
		}while((TransmitMailbox==CAN_TxStatus_NoMailBox)&&(i<0x7fff));
		if(i==0x7fff)
			return;
		i=0;
		while( (CAN_TransmitStatus(CAN1,TransmitMailbox) != CANTXOK)	&&(i<0x7fff) )
			i++;
		
		/*?receive*/
		RxMessage.StdId=0x00;
		RxMessage.IDE=CAN_ID_STD;
		RxMessage.DLC=0;
		RxMessage.Data[0]=0x00;
		RxMessage.Data[1]=0x00;
		CAN_Receive(CAN1,CAN_FIFO0, &RxMessage);
	}
	
	
	uint32_t checksumnow;
	void USB_LP_CAN1_RX0_IRQHandler(void)//CAN 中断接收程序 
	{ 
		int i,j;
		CanRxMsg  RxMessage;
		RxMessage.StdId=0x00;
		RxMessage.ExtId=0x00;
		RxMessage.IDE=0;
		RxMessage.DLC=0;
		RxMessage.FMI=0;
		for(int i=0;i<8;i++)
			RxMessage.Data[i]=0x00;
		RxMessage.Data[1]=0x00;
		CAN_Receive(CAN1,CAN_FIFO0, &RxMessage); 

		if(RxMessage.IDE==0)		//标准数据包
		{
		//	CanId_IDE					= (RxMessage.StdId>>31)&0x01;
		//	CanId_SRR					=	(RxMessage.StdId>>30)&0x01;
		//	CanId_RTR					=	(RxMessage.StdId>>29)&0x01;
			CanId_CANtype			=	(RxMessage.StdId>>7)&0x0F;
			CanId_DataNumber	= (RxMessage.StdId>>5)&0x03;
			cheakfg						=(RxMessage.StdId)&0x1f;
			if(timerfg>=15000)
				CAN_R_LED(SON);
			if(CanId_CANtype==0)//点灯信息
			{
				CAN_R_LED(SON);
				if(CanId_DataNumber==2)//第二包数据
				{
					for(int i=0;i<8;i++)
						canbuff[i+8]=RxMessage.Data[i];
					canreadfg=1;
					cheakfgS=cheakfg;
				}
				else if(CanId_DataNumber==1)//第一包数据
				{
					for(int i=0;i<8;i++)
						canbuff[i]=RxMessage.Data[i];
					cheakfgf=cheakfg;
				}
			}
			else if(CanId_CANtype==1)//反馈信息
			{
				cheakfg=((RxMessage.StdId>>3)&0x0f);
				Checkreplybuff[cheakfg].start=1;
				for(int i=0;i<8;i++)
					Checkreplybuff[cheakfg].cmd[i]=RxMessage.Data[i];
			}
			else if(CanId_CANtype==3)//接管配置
			{
				TakeOverorder			=(RxMessage.StdId>>6)&0x01;			//是否需要接管命令
				checkY_FLASHorder	=(RxMessage.StdId>>5)&0x01;		//异常是否需要黄闪指令
				checkVoltageorder	=(RxMessage.StdId>>4)&0x01;		//电压检测
				checkCurrentorder	=(RxMessage.StdId>>3)&0x01;		//电流检测			
				Y_FLASHorder			=(RxMessage.StdId>>2)&0x01;		//是否硬件黄闪命令				
				//	checkY_FLASHorder=1;
			}
		}
		else if(RxMessage.IDE==0x04)	//扩展数据包
		{
			CanId_CANtype			=	(RxMessage.ExtId>>25)&0x07;
			CanId_DataNumber	= (RxMessage.ExtId)&0x1ffffff;
			if(CanId_CANtype==2)//接管信息
			{
				if(CanId_DataNumber==0)
				{
					checksum=(RxMessage.Data[3]);
					checksum=checksum<<8;
					checksum=checksum+(RxMessage.Data[2]);
					checksum=checksum<<8;
					checksum=checksum+(RxMessage.Data[1]);
					checksum=checksum<<8;
					checksum=checksum+(RxMessage.Data[0]);

					arraynu=(RxMessage.Data[5]);
					arraynu=arraynu<<8;
					arraynu=arraynu+(RxMessage.Data[4]);
					
					framenum=(RxMessage.Data[7]);
					framenum=framenum<<8;
					framenum=framenum+(RxMessage.Data[6]);
					if(arraynu>160)
					{
						framenum=0;
						arraynu=0;
					}
					
				//	checksumnow=0;
				}
				else if(CanId_DataNumber<=framenum)
				{
				/*	for(i=0;i<8;i++) 
						checksumnow += RxMessage.Data[i];*/
					if(CanId_DataNumber%2==0)	//第二数据包
					{
						for(i=0;i<7;i++)
							TakeOverStrstorage[(CanId_DataNumber-1)/2].cmd[i+8]=RxMessage.Data[i];
						TakeOverStrstorage[(CanId_DataNumber-1)/2].duration=RxMessage.Data[7];
					}
					else											//第一数据包
					{
						for(i=0;i<8;i++)
							TakeOverStrstorage[(CanId_DataNumber-1)/2].cmd[i]=RxMessage.Data[i];						
					}
					if(CanId_DataNumber==framenum)
					{
						//校验
						checksumnow=0;
						for(i=0;i<arraynu;i++)
						{
							for(j=0;j<15;j++)
								checksumnow+=TakeOverStrstorage[i].cmd[j];
							checksumnow+=TakeOverStrstorage[i].duration;
						}
						if(checksumnow==checksum)
						{
							for(i=0;i<arraynu;i++)
							{
								TakeOverStruse[i].duration=TakeOverStrstorage[i].duration;
								for(j=0;j<15;j++)
								{
									TakeOverStruse[i].cmd[j]=TakeOverStrstorage[i].cmd[j];
								}
							}
							TakeOverNumbuse=arraynu;
						}
					}
				}
			}
		}
	}

	