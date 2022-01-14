#include "sys.h"
//#include "delay.h"
#include "led.h"
#include "main.h"

/*void Delay(__IO uint32_t nCount);

void Delay(__IO uint32_t nCount)
{
  while(nCount--){}
}*/


//全局变量定义
uint8_t Blink_Id=0u,Blink_Id_Old=0u,BOARD_ADDRESS=0u,Can_Buff[8],Light_Buff[4],CAN_Send_Fg=0u;
uint32_t Timer_Fg=0u,Timer_Fg1=0u; 

int main(void)
{
	HAL_Init();                    	 			//初始化HAL库    
	Stm32_Clock_Init(RCC_PLL_MUL9);   			//设置时钟,72M
	//delay_init(72);
	Led_Init();
	Board_Address_Init();
	
	Board_Address_Get();
	while(1)
	{
	Light();
	}
}
