#include "sys.h"
#include "delay.h"
#include "led.h"
#include "main.h"

//灯控板地址对应管脚初始化
void Board_Address_Init(void)
{
     GPIO_InitTypeDef GPIO_Initure;

    //这里时钟在初始化灯组时开启过，重复开启无影响，只在程序启动后执行一次
	__HAL_RCC_GPIOB_CLK_ENABLE();               //开启GPIOB时钟

    //PB6,PB7,PB8,PB9 地址读取
    GPIO_Initure.Pin=GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9; 
    GPIO_Initure.Mode=GPIO_MODE_INPUT;           //输入
    GPIO_Initure.Pull=GPIO_PULLUP;               //上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;    //高速
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);

}

//读取灯控板对应地址
u8 Board_Address_Get(void)
{
    BOARD_ADDRESS=0;
	if (ADDR0==1) BOARD_ADDRESS+=1;
    if (ADDR1==1) BOARD_ADDRESS+=2;
    if (ADDR2==1) BOARD_ADDRESS+=4;
    if (ADDR3==1) BOARD_ADDRESS+=8;
    return BOARD_ADDRESS;
}
