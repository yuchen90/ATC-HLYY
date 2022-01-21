//�Ե������ѹ������ռ��ʱ�����жϵ������ѹ�Ƿ�����
#include "main.h"
#include "declaration.h"

//��Ӧ�������ѹ��ȡ���ų�ʼ��
void VACheak_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_Init;

    __HAL_RCC_GPIOA_CLK_ENABLE();           	//����GPIOAʱ��
	__HAL_RCC_GPIOB_CLK_ENABLE();               //����GPIOBʱ��
    __HAL_RCC_GPIOC_CLK_ENABLE();               //����GPIOCʱ��
    __HAL_RCC_GPIOD_CLK_ENABLE();               //����GPIODʱ��

    //PA 2,4,6,8
    GPIO_Init.Pin = GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_8; 	
    GPIO_Init.Mode = GPIO_MODE_INPUT;  	    //����
    GPIO_Init.Pull = GPIO_PULLUP;          	//����
    GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;    //����
    HAL_GPIO_Init(GPIOA,&GPIO_Init);

    //PB 0��3��4��5��10��12��14
    GPIO_Init.Pin = GPIO_PIN_0|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_10|GPIO_PIN_12|GPIO_PIN_14; 
    GPIO_Init.Mode = GPIO_MODE_INPUT;  	    //����
    GPIO_Init.Pull = GPIO_PULLUP;          	//����
    GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;    //����
    HAL_GPIO_Init(GPIOB,&GPIO_Init);

    //PC 0��2��4��6��7��8��9��10��11��12��14
    GPIO_Init.Pin = GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_14;
    GPIO_Init.Mode = GPIO_MODE_INPUT;  	     //����
    GPIO_Init.Pull = GPIO_PULLUP;          	//����
    GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;    //����
    HAL_GPIO_Init(GPIOC,&GPIO_Init);

    //PD 2
    GPIO_Init.Pin = GPIO_PIN_2; 	
    GPIO_Init.Mode = GPIO_MODE_INPUT;  	    //����
    GPIO_Init.Pull = GPIO_PULLUP;          	//����
    GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;    //����
    HAL_GPIO_Init(GPIOD,&GPIO_Init);
}


