//�ƿذ������ų�ʼ��
#include "stm32f1xx_hal.h"

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

void Light(void)
{

}
