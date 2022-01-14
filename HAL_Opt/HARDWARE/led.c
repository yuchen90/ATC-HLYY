//�ƿذ������ų�ʼ��
#include "stm32f1xx_hal.h"
#include "led.h"
#include "sys.h"
#include "delay.h"
#include "main.h"

//����������ų�ʼ��
void Led_Init(void)
{
    GPIO_InitTypeDef GPIO_Init;

    __HAL_RCC_GPIOA_CLK_ENABLE();           	//����GPIOAʱ��
	__HAL_RCC_GPIOB_CLK_ENABLE();               //����GPIOBʱ��
    __HAL_RCC_GPIOC_CLK_ENABLE();               //����GPIOCʱ��

    //PA3,PA5,PA7,PA9(mcu_run) PA0,PA1(CAN_TX&CAN_Rx)
    GPIO_Init.Pin=GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_7|GPIO_PIN_9|GPIO_PIN_0|GPIO_PIN_1; 	
    GPIO_Init.Mode=GPIO_MODE_OUTPUT_PP;  	//�������
    GPIO_Init.Pull=GPIO_PULLUP;          	//����
    GPIO_Init.Speed=GPIO_SPEED_FREQ_HIGH;    //����
    HAL_GPIO_Init(GPIOA,&GPIO_Init);

    //PB1,PB11,PB13,PB15
    GPIO_Init.Pin=GPIO_PIN_1|GPIO_PIN_11|GPIO_PIN_13|GPIO_PIN_15; 
    GPIO_Init.Mode=GPIO_MODE_OUTPUT_PP;  	//�������
    GPIO_Init.Pull=GPIO_PULLUP;          	//����
    GPIO_Init.Speed=GPIO_SPEED_FREQ_HIGH;    //����
    HAL_GPIO_Init(GPIOB,&GPIO_Init);

    //PC1,PC3,PC5,PC13,PC15,
    GPIO_Init.Pin=GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_13|GPIO_PIN_15;
    GPIO_Init.Mode=GPIO_MODE_OUTPUT_PP;  	//�������
    GPIO_Init.Pull=GPIO_PULLUP;          	//����
    GPIO_Init.Speed=GPIO_SPEED_FREQ_HIGH;    //����
    HAL_GPIO_Init(GPIOC,&GPIO_Init);

}


//��������Ϣ������CANЭ��ȷ�ϵ���������״̬
void Light(void)
{
	uint64_t Lightdata=0;
	uint32_t i;
	//�Ȱ�CAN������Ϣ������
	for (i=0;i<8;i++)
	{
		Lightdata=Lightdata<<8;
		Lightdata=Lightdata+Can_Buff[7-i];
	}
	BOARD_ADDRESS=BOARD_ADDRESS%5; //�����CAN������ȡ��������Ϣ�����0-4��5-9 ��ȡ����һ�£������ȰѸ�λ��ص�λ
	//��CANЭ����ȡ
	Light_Buff[0]=(Lightdata>>(BOARD_ADDRESS*12))&0x07;
	Light_Buff[1]=(Lightdata>>(BOARD_ADDRESS*12+3))&0x07;
	Light_Buff[2]=(Lightdata>>(BOARD_ADDRESS*12+6))&0x07;
	Light_Buff[3]=(Lightdata>>(BOARD_ADDRESS*12+9))&0x07;
	Blink_Id=(Lightdata>>60)&0x01;

	//�˴���ԭ�����������µ������жϣ���ʱ��֪����
	//if((Blink_Id==1)&&(Blink_Id_Old==0))	Timer_Fg1=0;
	Blink_Id_Old=Blink_Id;		  //��ǰ��˸ָʾ��Ϊ�ɵı�ʶ��������һ�εĶԱ�

	//���Ժ���
	Light_Buff[0]=0;Light_Buff[1]=1;Light_Buff[2]=2;Light_Buff[3]=3;

	//��ǰ�ƿذ��4��������
	switch(Light_Buff[0])//����1���
	{
		case 0:			//��� 
				R1=LED_OFF;
				Y1=LED_OFF;
				G1=LED_OFF;
			break;
		case 1:			//�̵�
				R1=LED_OFF;
				Y1=LED_OFF;
				G1=LED_ON;
			break;
		case 2:			//�Ƶ�
				R1=LED_OFF;
				Y1=LED_ON;
				G1=LED_OFF;
			break;
		case 3:			//���
				R1=LED_ON;
				Y1=LED_OFF;
				G1=LED_OFF;
			break;
		case 4:			//����
				if(Blink_Id==0)	//��
				{
					R1=LED_OFF;
					Y1=LED_OFF;
					G1=LED_OFF;
				}
				else				//��
				{
					R1=LED_OFF;
					Y1=LED_OFF;
					G1=LED_ON;
				}
			break;
		case 5:			//����
				if(Blink_Id==0)	//��
				{
					R1=LED_OFF;
					Y1=LED_OFF;
					G1=LED_OFF;
				}
				else				//��
				{
					R1=LED_OFF;
					Y1=LED_ON;
					G1=LED_OFF;
				}
			break;
		case 6:			//����
				if(Blink_Id==0)	//��
				{
					R1=LED_OFF;
					Y1=LED_OFF;
					G1=LED_OFF;
				}
				else				//��
				{
					R1=LED_ON;
					Y1=LED_OFF;
					G1=LED_OFF;
				}
			break;
		case 7:			//���
				R1=LED_ON;
				Y1=LED_ON;
				G1=LED_OFF;
			break;
	}
	
	switch(Light_Buff[1])//����2���
	{
		case 0:			//��� 
				R2=LED_OFF;
				Y2=LED_OFF;
				G2=LED_OFF;
			break;
		case 1:			//�̵�
				R2=LED_OFF;
				Y2=LED_OFF;
				G2=LED_ON;
			break;
		case 2:			//�Ƶ�
				R2=LED_OFF;
				Y2=LED_ON;
				G2=LED_OFF;
			break;
		case 3:			//���
				R2=LED_ON;
				Y2=LED_OFF;
				G2=LED_OFF;
			break;
		case 4:			//����
				if(Blink_Id==0)	//��
				{
					R2=LED_OFF;
					Y2=LED_OFF;
					G2=LED_OFF;
				}
				else				//��
				{
					R2=LED_OFF;
					Y2=LED_OFF;
					G2=LED_ON;
				}
			break;
		case 5:			//����
				if(Blink_Id==0)	//��
				{
					R2=LED_OFF;
					Y2=LED_OFF;
					G2=LED_OFF;
				}
				else				//��
				{
					R2=LED_OFF;
					Y2=LED_ON;
					G2=LED_OFF;
				}
			break;
		case 6:			//����
				if(Blink_Id==0)	//��
				{
					R2=LED_OFF;
					Y2=LED_OFF;
					G2=LED_OFF;
				}
				else				//��
				{
					R2=LED_ON;
					Y2=LED_OFF;
					G2=LED_OFF;
				}
			break;
		case 7:			//���
				R2=LED_ON;
				Y2=LED_ON;
				G2=LED_OFF;
			break;
	}
	
	switch(Light_Buff[2])//����3���
	{
		case 0:			//��� 
				R3=LED_OFF;
				Y3=LED_OFF;
				G3=LED_OFF;
			break;
		case 1:			//�̵�
				R3=LED_OFF;
				Y3=LED_OFF;
				G3=LED_ON;
			break;
		case 2:			//�Ƶ�
				R3=LED_OFF;
				Y3=LED_ON;
				G3=LED_OFF;
			break;
		case 3:			//���
				R3=LED_ON;
				Y3=LED_OFF;
				G3=LED_OFF;
			break;
		case 4:			//����
				if(Blink_Id==0)	//��
				{
					R3=LED_OFF;
					Y3=LED_OFF;
					G3=LED_OFF;
				}
				else				//��
				{
					R3=LED_OFF;
					Y3=LED_OFF;
					G3=LED_ON;
				}
			break;
		case 5:			//����
				if(Blink_Id==0)	//��
				{
					R3=LED_OFF;
					Y3=LED_OFF;
					G3=LED_OFF;
				}
				else				//��
				{
					R3=LED_OFF;
					Y3=LED_ON;
					G3=LED_OFF;
				}
			break;
		case 6:			//����
				if(Blink_Id==0)	//��
				{
					R3=LED_OFF;
					Y3=LED_OFF;
					G3=LED_OFF;
				}
				else				//��
				{
					R3=LED_ON;
					Y3=LED_OFF;
					G3=LED_OFF;
				}
			break;
		case 7:			//���
				R3=LED_ON;
				Y3=LED_ON;
				G3=LED_OFF;
			break;
	}

	switch(Light_Buff[3])//����4���
	{
		case 0:			//��� 
				R4=LED_OFF;
				Y4=LED_OFF;
				G4=LED_OFF;
			break;
		case 1:			//�̵�
				R4=LED_OFF;
				Y4=LED_OFF;
				G4=LED_ON;
			break;
		case 2:			//�Ƶ�
				R4=LED_OFF;
				Y4=LED_ON;
				G4=LED_OFF;
			break;
		case 3:			//���
				R4=LED_ON;
				Y4=LED_OFF;
				G4=LED_OFF;
			break;
		case 4:			//����
				if(Blink_Id==0)	//��
				{
					R4=LED_OFF;
					Y4=LED_OFF;
					G4=LED_OFF;
				}
				else				//��
				{
					R4=LED_OFF;
					Y4=LED_OFF;
					G4=LED_ON;
				}
			break;
		case 5:			//����
				if(Blink_Id==0)	//��
				{
					R4=LED_OFF;
					Y4=LED_OFF;
					G4=LED_OFF;
				}
				else				//��
				{
					R4=LED_OFF;
					Y4=LED_ON;
					G4=LED_OFF;
				}
			break;
		case 6:			//����
				if(Blink_Id==0)	//��
				{
					R4=LED_OFF;
					Y4=LED_OFF;
					G4=LED_OFF;
				}
				else				//��
				{
					R4=LED_ON;
					Y4=LED_OFF;
					G4=LED_OFF;
				}
			break;
		case 7:			//���
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
