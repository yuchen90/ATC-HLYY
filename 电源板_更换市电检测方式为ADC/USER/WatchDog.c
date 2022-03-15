////////////////////////////////////////////////////////////////
/*
喂狗
*/
////////////////////////////////////////////////////////////////
#include "stm32f10x.h"

	#include <stdio.h>
	
#include "common.h"
#include "data.h"




void WatchDog_int(uint16_t Settime_ms)// 独立看门狗IWDG设置
{
     /* Enable write access to IWDG_PR and IWDG_RLR registers */
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
   /* IWDG counter clock: 32KHz(LSI) / 32 = 1KHz */
  IWDG_SetPrescaler(IWDG_Prescaler_32); //独立看门狗预分频为32

   /* Set counter reload value to 1000 */
  IWDG_SetReload(Settime_ms);//设置IWDG重装载值 范围为 0~0x0FFF;

    /* Reload IWDG counter */
  IWDG_ReloadCounter();//按照重装载的寄存器的值来重装载IWDG计数器

    /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
  IWDG_Enable();//使能 独立看门狗
}

