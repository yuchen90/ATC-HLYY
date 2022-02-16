//�ƿذ������ų�ʼ��
#include "main.h"
#include "declaration.h"

/**
  * @brief  ��ʼ�������Ӧ�ܽ�
  * @param  None
  * @retval None
  */
void Led_Init(void)
{
    GPIO_InitTypeDef GPIO_Init;

    __HAL_RCC_GPIOA_CLK_ENABLE();           	//����GPIOAʱ��
	__HAL_RCC_GPIOB_CLK_ENABLE();               //����GPIOBʱ��
    __HAL_RCC_GPIOC_CLK_ENABLE();               //����GPIOCʱ��

    //PA3,PA5,PA7,PA9(mcu_run) PA0,PA1(CAN_TX_LED&CAN_Rx_LED)
    GPIO_Init.Pin = GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_7|GPIO_PIN_9|GPIO_PIN_0|GPIO_PIN_1; 	
    GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;  	//�������
    GPIO_Init.Pull = GPIO_PULLUP;          	//����
    GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;    //����
    HAL_GPIO_Init(GPIOA,&GPIO_Init);

    //PB1,PB11,PB13,PB15
    GPIO_Init.Pin = GPIO_PIN_1|GPIO_PIN_11|GPIO_PIN_13|GPIO_PIN_15; 
    GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;  	//�������
    GPIO_Init.Pull = GPIO_PULLUP;          	//����
    GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;    //����
    HAL_GPIO_Init(GPIOB,&GPIO_Init);

    //PC1,PC3,PC5,PC13,PC15,
    GPIO_Init.Pin = GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_13|GPIO_PIN_15;
    GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;  	//�������
    GPIO_Init.Pull = GPIO_PULLUP;          	//����
    GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;    //����
    HAL_GPIO_Init(GPIOC,&GPIO_Init);

}


/**
  * @brief  ��CAN���ձ��ģ���������
  * @param  None
  * @retval None
  */
void Led_Display(void)
{
	uint64_t Lightdata = 0u;
	uint32_t i;
	//�Ȱ�CAN������Ϣ������
	for (i=0u;i<8u;i++)
	{
		Lightdata = Lightdata<<8u;
		Lightdata = Lightdata+Can_Buff[7-i];
	}
	BOARD_ADDRESS=BOARD_ADDRESS%5; //�����CAN������ȡ��������Ϣ�����0-4��5-9 ��ȡ����һ�£������ȰѸ�λ��ص�λ
	//��CANЭ����ȡ
	Light_Buff[0] = (Lightdata>>(BOARD_ADDRESS*12u))&0x07u;
	Light_Buff[1] = (Lightdata>>(BOARD_ADDRESS*12u+3u))&0x07u;
	Light_Buff[2] = (Lightdata>>(BOARD_ADDRESS*12u+6u))&0x07u;
	Light_Buff[3] = (Lightdata>>(BOARD_ADDRESS*12u+9u))&0x07u;
	Blink_Id = (Lightdata>>60u)&0x01u;

	//�˴����������˸״̬����ô��Timer_Fg1=0; ��ʱTimer_Fg1 �� Timer_Fg�� 5000 �� ����ֵ
	if((Blink_Id == 1) && (Blink_Id_Before == 0))	
	Timer_Fg1 = 0;

	Blink_Id_Before = Blink_Id;		  //��ǰ��˸ָʾ��Ϊ�ɵı�ʶ��������һ�εĶԱ�

	//��ǰ�ƿذ��4��������
	switch(Light_Buff[0])//����1���
	{
		case 0:			//��� 
				R1 = LED_OFF;
				Y1 = LED_OFF;
				G1 = LED_OFF;
			break;
		case 1:			//�̵�
				R1 = LED_OFF;
				Y1 = LED_OFF;
				G1 = LED_ON;
			break;
		case 2:			//�Ƶ�
				R1 = LED_OFF;
				Y1 = LED_ON;
				G1 = LED_OFF;
			break;
		case 3:			//���
				R1 = LED_ON;
				Y1 = LED_OFF;
				G1 = LED_OFF;
			break;
		case 4:			//����
				if(Blink_Id == 0)	//��
				{
					R1 = LED_OFF;
					Y1 = LED_OFF;
					G1 = LED_OFF;
				}
				else				//��
				{
					R1 = LED_OFF;
					Y1 = LED_OFF;
					G1 = LED_ON;
				}
			break;
		case 5:			//����
				if(Blink_Id == 0)	//��
				{
					R1 = LED_OFF;
					Y1 = LED_OFF;
					G1 = LED_OFF;
				}
				else				//��
				{
					R1 = LED_OFF;
					Y1 = LED_ON;
					G1 = LED_OFF;
				}
			break;
		case 6:			//����
				if(Blink_Id == 0)	//��
				{
					R1 = LED_OFF;
					Y1 = LED_OFF;
					G1 = LED_OFF;
				}
				else				//��
				{
					R1 = LED_ON;
					Y1 = LED_OFF;
					G1 = LED_OFF;
				}
			break;
		case 7:			//���
				R1 = LED_ON;
				Y1 = LED_ON;
				G1 = LED_OFF;
			break;
	}

		switch(Light_Buff[1])//����2���
	{
		case 0:			//��� 
				R2 = LED_OFF;
				Y2 = LED_OFF;
				G2 = LED_OFF;
			break;
		case 1:			//�̵�
				R2 = LED_OFF;
				Y2 = LED_OFF;
				G2 = LED_ON;
			break;
		case 2:			//�Ƶ�
				R2 = LED_OFF;
				Y2 = LED_ON;
				G2 = LED_OFF;
			break;
		case 3:			//���
				R2 = LED_ON;
				Y2 = LED_OFF;
				G2 = LED_OFF;
			break;
		case 4:			//����
				if(Blink_Id == 0)	//��
				{
					R2 = LED_OFF;
					Y2 = LED_OFF;
					G2 = LED_OFF;
				}
				else				//��
				{
					R2 = LED_OFF;
					Y2 = LED_OFF;
					G2 = LED_ON;
				}
			break;
		case 5:			//����
				if(Blink_Id == 0)	//��
				{
					R2 = LED_OFF;
					Y2 = LED_OFF;
					G2 = LED_OFF;
				}
				else				//��
				{
					R2 = LED_OFF;
					Y2 = LED_ON;
					G2 = LED_OFF;
				}
			break;
		case 6:			//����
				if(Blink_Id == 0)	//��
				{
					R2 = LED_OFF;
					Y2 = LED_OFF;
					G2 = LED_OFF;
				}
				else				//��
				{
					R2 = LED_ON;
					Y2 = LED_OFF;
					G2 = LED_OFF;
				}
			break;
		case 7:			//���
				R2 = LED_ON;
				Y2 = LED_ON;
				G2 = LED_OFF;
			break;
	}

		switch(Light_Buff[2])//����3���
	{
		case 0:			//��� 
				R3 = LED_OFF;
				Y3 = LED_OFF;
				G3 = LED_OFF;
			break;
		case 1:			//�̵�
				R3 = LED_OFF;
				Y3 = LED_OFF;
				G3 = LED_ON;
			break;
		case 2:			//�Ƶ�
				R3 = LED_OFF;
				Y3 = LED_ON;
				G3 = LED_OFF;
			break;
		case 3:			//���
				R3 = LED_ON;
				Y3 = LED_OFF;
				G3 = LED_OFF;
			break;
		case 4:			//����
				if(Blink_Id == 0)	//��
				{
					R3 = LED_OFF;
					Y3 = LED_OFF;
					G3 = LED_OFF;
				}
				else				//��
				{
					R3 = LED_OFF;
					Y3 = LED_OFF;
					G3 = LED_ON;
				}
			break;
		case 5:			//����
				if(Blink_Id == 0)	//��
				{
					R3 = LED_OFF;
					Y3 = LED_OFF;
					G3 = LED_OFF;
				}
				else				//��
				{
					R3 = LED_OFF;
					Y3 = LED_ON;
					G3 = LED_OFF;
				}
			break;
		case 6:			//����
				if(Blink_Id == 0)	//��
				{
					R3 = LED_OFF;
					Y3 = LED_OFF;
					G3 = LED_OFF;
				}
				else				//��
				{
					R3 = LED_ON;
					Y3 = LED_OFF;
					G3 = LED_OFF;
				}
			break;
		case 7:			//���
				R3 = LED_ON;
				Y3 = LED_ON;
				G3 = LED_OFF;
			break;
	}

		switch(Light_Buff[3])//����4���
	{
		case 0:			//��� 
				R4 = LED_OFF;
				Y4 = LED_OFF;
				G4 = LED_OFF;
			break;
		case 1:			//�̵�
				R4 = LED_OFF;
				Y4 = LED_OFF;
				G4 = LED_ON;
			break;
		case 2:			//�Ƶ�
				R4 = LED_OFF;
				Y4 = LED_ON;
				G4 = LED_OFF;
			break;
		case 3:			//���
				R4 = LED_ON;
				Y4 = LED_OFF;
				G4 = LED_OFF;
			break;
		case 4:			//����
				if(Blink_Id == 0)	//��
				{
					R4 = LED_OFF;
					Y4 = LED_OFF;
					G4 = LED_OFF;
				}
				else				//��
				{
					R4 = LED_OFF;
					Y4 = LED_OFF;
					G4 = LED_ON;
				}
			break;
		case 5:			//����
				if(Blink_Id == 0)	//��
				{
					R4 = LED_OFF;
					Y4 = LED_OFF;
					G4 = LED_OFF;
				}
				else				//��
				{
					R4 = LED_OFF;
					Y4 = LED_ON;
					G4 = LED_OFF;
				}
			break;
		case 6:			//����
				if(Blink_Id == 0)	//��
				{
					R4 = LED_OFF;
					Y4 = LED_OFF;
					G4 = LED_OFF;
				}
				else				//��
				{
					R4 = LED_ON;
					Y4 = LED_OFF;
					G4 = LED_OFF;
				}
			break;
		case 7:			//���
				R4 = LED_ON;
				Y4 = LED_ON;
				G4 = LED_OFF;
			break;
	}
}
