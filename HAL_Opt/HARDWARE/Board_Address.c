#include "sys.h"
#include "delay.h"
#include "led.h"
#include "main.h"

//�ƿذ��ַ��Ӧ�ܽų�ʼ��
void Board_Address_Init(void)
{
     GPIO_InitTypeDef GPIO_Initure;

    //����ʱ���ڳ�ʼ������ʱ���������ظ�������Ӱ�죬ֻ�ڳ���������ִ��һ��
	__HAL_RCC_GPIOB_CLK_ENABLE();               //����GPIOBʱ��

    //PB6,PB7,PB8,PB9 ��ַ��ȡ
    GPIO_Initure.Pin=GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9; 
    GPIO_Initure.Mode=GPIO_MODE_INPUT;           //����
    GPIO_Initure.Pull=GPIO_PULLUP;               //����
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;    //����
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);

}

//��ȡ�ƿذ��Ӧ��ַ
u8 Board_Address_Get(void)
{
    BOARD_ADDRESS=0;
	if (ADDR0==1) BOARD_ADDRESS+=1;
    if (ADDR1==1) BOARD_ADDRESS+=2;
    if (ADDR2==1) BOARD_ADDRESS+=4;
    if (ADDR3==1) BOARD_ADDRESS+=8;
    return BOARD_ADDRESS;
}
