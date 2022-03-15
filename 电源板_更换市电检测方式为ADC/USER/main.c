/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>
#include "main.h"
#include "common.h"


void WatchDog_int(uint16_t Settime_ms);
void init_gpio(void);
void init_can();
void TIM2_Config(u16 arr,u16 psc);
void uart2_init(void);
void init_sendcanbuff(void);
void sendMD();
void seekPointer();
void checklampreply();
void checklamp();	
	
int  main(void)
{
//	RCC_DeInit();

	timerfg1=0;
	init_gpio();
	init_can();
	WatchDog_int(1000);
	TIM2_Config(20,360);			//4M  1 0.1ms   10 1ms       8  2  0.1ms    20   0.1ms
	uart2_init();
	
	TakeOverNumbuse=0;
//	init_sendcanbuff();
	cheakfg=0;
	runtime=0;
	sendMD();
	cheakmdfg=0;
	TakeOverorder=1;
	Y_FLASHorder=0;
	
	
	
  while (1)
  {
		IWDG_ReloadCounter();//喂狗
		if(timerfg1%10000<5000)		
		{			
			MCU_RUN(SON);	
		}		else 		
		{
			MCU_RUN(SOFF);
		}

		if(canreadfg==1)//CAN有数据来了
		{
			u8 address;
			seekPointer();
			cheakmdfg++;
			if(cheakmdfg>=4)
				cheakmdfg=0;
			timerfg=0;
			canreadfg=0;
			cheakfg2=2;
		}
		if(cheakfg2==2)
		{
			checklamp();
		}

		if((TakeOverNumbuse>0)&&(TakeOverorder==1))
		{
			if(timerfg==17500)
			{
				CAN_T_LED(SON);
				CAN_R_LED(SOFF);
				sendcan(1);
				CAN_T_LED(SOFF);
				CAN_R_LED(SON);
			}
			else if(timerfg==20000)
			{
				CAN_T_LED(SON);
				CAN_R_LED(SOFF);
				sendcan(2);
				CAN_T_LED(SOFF);
				CAN_R_LED(SON);
			}
			else if(timerfg==22500)
			{
				CAN_T_LED(SON);
				CAN_R_LED(SOFF);
				sendcan(3);
				CAN_T_LED(SOFF);
				CAN_R_LED(SON);
				runtime++;
				if(runtime>=TakeOverStruse[TakeOverPointeruse].duration)
				{
					runtime=0;
					TakeOverPointeruse++;
					if(TakeOverPointeruse>=TakeOverNumbuse)
						TakeOverPointeruse=0;
				}
			}
			else if(timerfg==15000)
			{
				sendMD();
				CAN_T_LED(SON);
				CAN_R_LED(SOFF);
				sendcan(0);
				CAN_T_LED(SOFF);
				CAN_R_LED(SON);
			}
			
			if((timerfg%2500==1000)&&(timerfg>=15000))
			{
				checklampreply();
			}
		}
		
			if((timerfg<1200)&&(timerfg>600))
			{
				if(Y_F_Voltage==0)
				{
				//	if(Voltage_R1_numb<20000)
						Voltage_R2_numb++;
				}
				else
				{
					//Voltage_R2_numb=Voltage_R2_numb;
					Voltage_R4_numb++;
				}
				
			}
			if((timerfg>600)&&(timerfg<1200))
			{
				//if(timerfg%8==0)
				if(Y_F_Voltage==0)
				{
				//	if(Voltage_R1_numb<20000)
						Voltage_R1_numb++;
				}
				else
				{
				//	Voltage_R1_numb=Voltage_R1_numb;
					Voltage_R3_numb++;
				}
				
			}
		
  }
}

/*
unsigned char sendcanbuffcmdsss[11][16]={
															{0x00,0x00,0x00,0x00,0x06,0x59,0x65,0x96,0x59,0x6D,0xB2,0x49,0x6D,0xB2,0x49},
															{0x00,0x00,0x00,0x00,0x07,0x1C,0x65,0x96,0x59,0x6D,0xB8,0x49,0x6D,0xB8,0x49},
															{0x00,0x00,0x00,0x00,0x07,0x1C,0x71,0xC7,0x1C,0x6D,0xB9,0x24,0x6D,0xB9,0x24},
															{0x00,0x00,0x00,0x00,0x06,0xDB,0x69,0xA6,0x9A,0x6D,0xB6,0x92,0x6D,0xB6,0x92},
															{0x00,0x00,0x00,0x00,0x06,0xDB,0x6D,0xB6,0xDB,0x6D,0xB6,0xDB,0x6D,0xB6,0xDB},
																
															{0x00,0x00,0x00,0x00,0x02,0xCB,0x2C,0xB2,0xCB,0x24,0x96,0xDB,0x24,0x96,0xDB},
															{0x00,0x00,0x00,0x00,0x08,0xE3,0x2C,0xB2,0xCB,0x84,0x96,0xDB,0x84,0x96,0xDB},
															{0x00,0x00,0x00,0x00,0x08,0xE3,0x8E,0x38,0xE3,0x92,0x46,0xDB,0x92,0x46,0xDB},
															{0x00,0x00,0x00,0x00,0x06,0xDB,0x4D,0x34,0xD3,0x69,0x26,0xDB,0x69,0x26,0xDB},
															{0x00,0x00,0x00,0x00,0x06,0xDB,0x6D,0xB6,0xDB,0x6D,0xB6,0xDB,0x6D,0xB6,0xDB}
};
/*
void init_sendcanbuff()
{
	//TakeOverNumbuse=6;
	
}*/



