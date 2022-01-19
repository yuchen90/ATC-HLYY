//灯控板点灯引脚初始化
#include "main.h"
#include "declaration.h"

//灯组相关引脚初始化
void Led_Init(void)
{
    GPIO_InitTypeDef GPIO_Init;

    __HAL_RCC_GPIOA_CLK_ENABLE();           	//开启GPIOA时钟
	__HAL_RCC_GPIOB_CLK_ENABLE();               //开启GPIOB时钟
    __HAL_RCC_GPIOC_CLK_ENABLE();               //开启GPIOC时钟

    //PA3,PA5,PA7,PA9(mcu_run) PA0,PA1(CAN_TX_LED&CAN_Rx_LED)
    GPIO_Init.Pin=GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_7|GPIO_PIN_9|GPIO_PIN_0|GPIO_PIN_1; 	
    GPIO_Init.Mode=GPIO_MODE_OUTPUT_PP;  	//推挽输出
    GPIO_Init.Pull=GPIO_PULLUP;          	//上拉
    GPIO_Init.Speed=GPIO_SPEED_FREQ_HIGH;    //高速
    HAL_GPIO_Init(GPIOA,&GPIO_Init);

    //PB1,PB11,PB13,PB15
    GPIO_Init.Pin=GPIO_PIN_1|GPIO_PIN_11|GPIO_PIN_13|GPIO_PIN_15; 
    GPIO_Init.Mode=GPIO_MODE_OUTPUT_PP;  	//推挽输出
    GPIO_Init.Pull=GPIO_PULLUP;          	//上拉
    GPIO_Init.Speed=GPIO_SPEED_FREQ_HIGH;    //高速
    HAL_GPIO_Init(GPIOB,&GPIO_Init);

    //PC1,PC3,PC5,PC13,PC15,
    GPIO_Init.Pin=GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_13|GPIO_PIN_15;
    GPIO_Init.Mode=GPIO_MODE_OUTPUT_PP;  	//推挽输出
    GPIO_Init.Pull=GPIO_PULLUP;          	//上拉
    GPIO_Init.Speed=GPIO_SPEED_FREQ_HIGH;    //高速
    HAL_GPIO_Init(GPIOC,&GPIO_Init);

}


//灯组点灯信息，根据CAN协议确认单个灯组点灯状态
void Led_Display(void)
{
	uint64_t Lightdata=0u;
	uint32_t i;
	//先把CAN缓存信息读出来
	for (i=0u;i<8u;i++)
	{
		Lightdata=Lightdata<<8u;
		Lightdata=Lightdata+Can_Buff[7-i];
	}
	BOARD_ADDRESS=BOARD_ADDRESS%5; //下面从CAN缓存提取灯组点灯信息，编号0-4与5-9 提取方法一致，所有先把高位变回低位
	//按CAN协议提取
	Light_Buff[0]=(Lightdata>>(BOARD_ADDRESS*12u))&0x07u;
	Light_Buff[1]=(Lightdata>>(BOARD_ADDRESS*12u+3u))&0x07u;
	Light_Buff[2]=(Lightdata>>(BOARD_ADDRESS*12u+6u))&0x07u;
	Light_Buff[3]=(Lightdata>>(BOARD_ADDRESS*12u+9u))&0x07u;
	Blink_Id=(Lightdata>>60u)&0x01u;

	//此处在原函数加了如下的条件判断，暂时不知用意
	//if((Blink_Id==1)&&(Blink_Id_Old==0))	Timer_Fg1=0;
	Blink_Id_Old=Blink_Id;		  //当前闪烁指示变为旧的标识，用于下一次的对比

	//测试函数
	//Light_Buff[0]=0u;Light_Buff[1]=1u;Light_Buff[2]=2u;Light_Buff[3]=3u;

	//当前灯控板的4个灯组点灯
	switch(Light_Buff[0])//灯组1输出
	{
		case 0:			//灭灯 
				R1=LED_OFF;
				Y1=LED_OFF;
				G1=LED_OFF;
			break;
		case 1:			//绿灯
				R1=LED_OFF;
				Y1=LED_OFF;
				G1=LED_ON;
			break;
		case 2:			//黄灯
				R1=LED_OFF;
				Y1=LED_ON;
				G1=LED_OFF;
			break;
		case 3:			//红灯
				R1=LED_ON;
				Y1=LED_OFF;
				G1=LED_OFF;
			break;
		case 4:			//绿闪
				if(Blink_Id==0)	//灭
				{
					R1=LED_OFF;
					Y1=LED_OFF;
					G1=LED_OFF;
				}
				else				//亮
				{
					R1=LED_OFF;
					Y1=LED_OFF;
					G1=LED_ON;
				}
			break;
		case 5:			//黄闪
				if(Blink_Id==0)	//灭
				{
					R1=LED_OFF;
					Y1=LED_OFF;
					G1=LED_OFF;
				}
				else				//亮
				{
					R1=LED_OFF;
					Y1=LED_ON;
					G1=LED_OFF;
				}
			break;
		case 6:			//红闪
				if(Blink_Id==0)	//灭
				{
					R1=LED_OFF;
					Y1=LED_OFF;
					G1=LED_OFF;
				}
				else				//亮
				{
					R1=LED_ON;
					Y1=LED_OFF;
					G1=LED_OFF;
				}
			break;
		case 7:			//红黄
				R1=LED_ON;
				Y1=LED_ON;
				G1=LED_OFF;
			break;
	}
	
	switch(Light_Buff[1])//灯组2输出
	{
		case 0:			//灭灯 
				R2=LED_OFF;
				Y2=LED_OFF;
				G2=LED_OFF;
			break;
		case 1:			//绿灯
				R2=LED_OFF;
				Y2=LED_OFF;
				G2=LED_ON;
			break;
		case 2:			//黄灯
				R2=LED_OFF;
				Y2=LED_ON;
				G2=LED_OFF;
			break;
		case 3:			//红灯
				R2=LED_ON;
				Y2=LED_OFF;
				G2=LED_OFF;
			break;
		case 4:			//绿闪
				if(Blink_Id==0)	//灭
				{
					R2=LED_OFF;
					Y2=LED_OFF;
					G2=LED_OFF;
				}
				else				//亮
				{
					R2=LED_OFF;
					Y2=LED_OFF;
					G2=LED_ON;
				}
			break;
		case 5:			//黄闪
				if(Blink_Id==0)	//灭
				{
					R2=LED_OFF;
					Y2=LED_OFF;
					G2=LED_OFF;
				}
				else				//亮
				{
					R2=LED_OFF;
					Y2=LED_ON;
					G2=LED_OFF;
				}
			break;
		case 6:			//红闪
				if(Blink_Id==0)	//灭
				{
					R2=LED_OFF;
					Y2=LED_OFF;
					G2=LED_OFF;
				}
				else				//亮
				{
					R2=LED_ON;
					Y2=LED_OFF;
					G2=LED_OFF;
				}
			break;
		case 7:			//红黄
				R2=LED_ON;
				Y2=LED_ON;
				G2=LED_OFF;
			break;
	}
	
	switch(Light_Buff[2])//灯组3输出
	{
		case 0:			//灭灯 
				R3=LED_OFF;
				Y3=LED_OFF;
				G3=LED_OFF;
			break;
		case 1:			//绿灯
				R3=LED_OFF;
				Y3=LED_OFF;
				G3=LED_ON;
			break;
		case 2:			//黄灯
				R3=LED_OFF;
				Y3=LED_ON;
				G3=LED_OFF;
			break;
		case 3:			//红灯
				R3=LED_ON;
				Y3=LED_OFF;
				G3=LED_OFF;
			break;
		case 4:			//绿闪
				if(Blink_Id==0)	//灭
				{
					R3=LED_OFF;
					Y3=LED_OFF;
					G3=LED_OFF;
				}
				else				//亮
				{
					R3=LED_OFF;
					Y3=LED_OFF;
					G3=LED_ON;
				}
			break;
		case 5:			//黄闪
				if(Blink_Id==0)	//灭
				{
					R3=LED_OFF;
					Y3=LED_OFF;
					G3=LED_OFF;
				}
				else				//亮
				{
					R3=LED_OFF;
					Y3=LED_ON;
					G3=LED_OFF;
				}
			break;
		case 6:			//红闪
				if(Blink_Id==0)	//灭
				{
					R3=LED_OFF;
					Y3=LED_OFF;
					G3=LED_OFF;
				}
				else				//亮
				{
					R3=LED_ON;
					Y3=LED_OFF;
					G3=LED_OFF;
				}
			break;
		case 7:			//红黄
				R3=LED_ON;
				Y3=LED_ON;
				G3=LED_OFF;
			break;
	}

	switch(Light_Buff[3])//灯组4输出
	{
		case 0:			//灭灯 
				R4=LED_OFF;
				Y4=LED_OFF;
				G4=LED_OFF;
			break;
		case 1:			//绿灯
				R4=LED_OFF;
				Y4=LED_OFF;
				G4=LED_ON;
			break;
		case 2:			//黄灯
				R4=LED_OFF;
				Y4=LED_ON;
				G4=LED_OFF;
			break;
		case 3:			//红灯
				R4=LED_ON;
				Y4=LED_OFF;
				G4=LED_OFF;
			break;
		case 4:			//绿闪
				if(Blink_Id==0)	//灭
				{
					R4=LED_OFF;
					Y4=LED_OFF;
					G4=LED_OFF;
				}
				else				//亮
				{
					R4=LED_OFF;
					Y4=LED_OFF;
					G4=LED_ON;
				}
			break;
		case 5:			//黄闪
				if(Blink_Id==0)	//灭
				{
					R4=LED_OFF;
					Y4=LED_OFF;
					G4=LED_OFF;
				}
				else				//亮
				{
					R4=LED_OFF;
					Y4=LED_ON;
					G4=LED_OFF;
				}
			break;
		case 6:			//红闪
				if(Blink_Id==0)	//灭
				{
					R4=LED_OFF;
					Y4=LED_OFF;
					G4=LED_OFF;
				}
				else				//亮
				{
					R4=LED_ON;
					Y4=LED_OFF;
					G4=LED_OFF;
				}
			break;
		case 7:			//红黄
				R4=LED_ON;
				Y4=LED_ON;
				G4=LED_OFF;
			break;
	}

}

/*void Light(void) 
{
    	R1=LED_ON;
		delay_ms(1000);
		Y1=LED_ON;
		delay_ms(1000);
		G1=LED_ON;
		delay_ms(1000);	
        R2=LED_ON;
		delay_ms(1000);
		Y2=LED_ON;
		delay_ms(1000);
		G2=LED_ON;
		delay_ms(1000);	
        R3=LED_ON;
		delay_ms(1000);
		Y3=LED_ON;
		delay_ms(1000);
		G3=LED_ON;
		delay_ms(1000);	
        R4=LED_ON;
		delay_ms(1000);
		Y4=LED_ON;
		delay_ms(1000);
		G4=LED_ON;
		delay_ms(1000);	
        R1=LED_OFF;
		Y1=LED_OFF;
		G1=LED_OFF;
        R2=LED_OFF;
		Y2=LED_OFF;
		G2=LED_OFF;
        R3=LED_OFF;
		Y3=LED_OFF;
		G3=LED_OFF;
        R4=LED_OFF;
		Y4=LED_OFF;
		G4=LED_OFF;
}*/
