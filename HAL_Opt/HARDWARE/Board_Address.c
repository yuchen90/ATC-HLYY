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
	  __HAL_RCC_GPIOB_CLK_ENABLE();                  //����GPIOBʱ��

    //PB6,PB7,PB8,PB9 ��ַ��ȡ
    GPIO_Initure.Pin=GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9; 
    GPIO_Initure.Mode=GPIO_MODE_INPUT;           //����
    GPIO_Initure.Pull=GPIO_PULLUP;               //����
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
}

/**
  * @brief  ��ȡ��ַ�ܽţ���ֵ��Board_Address
  * @param  None
  * @retval Board_Address����ǰ�ƿذ��ַ���� [0,9] ������һ������
  */
uint8_t Board_Address_Get(void)
{
    Board_Address=0;
	  if (ADDR0==1) Board_Address+=1;
    if (ADDR1==1) Board_Address+=2;
    if (ADDR2==1) Board_Address+=4;
    if (ADDR3==1) Board_Address+=8;
    return Board_Address;
}
