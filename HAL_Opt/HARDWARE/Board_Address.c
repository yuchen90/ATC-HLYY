#include "main.h"
#include "declaration.h"

/**
  * @brief  ��ַ��Ӧ�ܽų�ʼ��
  * @param  None
  * @retval None
  */
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

/**
  * @brief  ��ȡ��ַ�ܽţ���ֵ��BOARD_ADDRESS
  * @param  None
  * @retval BOARD_ADDRESS����ǰ�ƿذ��ַ���� [0,9] ������һ������
  */
uint8_t Board_Address_Get(void)
{
    BOARD_ADDRESS=0;
	if (ADDR0==1) BOARD_ADDRESS+=1;
    if (ADDR1==1) BOARD_ADDRESS+=2;
    if (ADDR2==1) BOARD_ADDRESS+=4;
    if (ADDR3==1) BOARD_ADDRESS+=8;
    return BOARD_ADDRESS;
}
