//�ƿذ������ų�ʼ��
#include "stm32f1xx_hal.h"
#include "led.h"
#include "sys.h"
#include "delay.h"

//����������ų�ʼ��
void Led_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOA_CLK_ENABLE();           	//����GPIOAʱ��
	__HAL_RCC_GPIOB_CLK_ENABLE();               //����GPIOBʱ��
    __HAL_RCC_GPIOC_CLK_ENABLE();               //����GPIOCʱ��

    //PA3,PA5,PA7
    GPIO_Initure.Pin=GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_7; 	
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//�������
    GPIO_Initure.Pull=GPIO_PULLUP;          	//����
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;    //����
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);

    //PB1,PB11,PB13,PB15
    GPIO_Initure.Pin=GPIO_PIN_1|GPIO_PIN_11|GPIO_PIN_13|GPIO_PIN_15; 
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//�������
    GPIO_Initure.Pull=GPIO_PULLUP;          	//����
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;    //����
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);

    //PC1,PC3,PC5,PC13,PC15,
    GPIO_Initure.Pin=GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_13|GPIO_PIN_15;
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//�������
    GPIO_Initure.Pull=GPIO_PULLUP;          	//����
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;    //����
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);

}

//��������Ϣ
void Light(void)
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
}
