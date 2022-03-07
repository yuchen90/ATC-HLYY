#include "main.h"
#include "declaration.h"

IWDG_HandleTypeDef IWDG_Handle;    //独立看门狗句柄

/**
  * @brief  初始化独立看门狗
  * @param  pre：分频数:IWDG_PRESCALER_4~IWDG_PRESCALER_256
  * @param  reload：自动重装载值,0~0XFFF.
  * 时间计算(大概):Tout=((4*2^prer)*rlr)/32 (ms).
  * @retval None
  */
 void IWDG_Init(uint8_t pre,uint_fast16_t reload)
{
    IWDG_Handle.Instance=IWDG;
    IWDG_Handle.Init.Prescaler=pre;	//设置IWDG分频系数
    IWDG_Handle.Init.Reload=reload;	//重装载值
    HAL_IWDG_Init(&IWDG_Handle);		//初始化IWDG,默认会开启独立看门狗
}

/**
  * @brief  喂独立看门狗
  * @param  None
  * @retval None
  */
void IWDG_Feed(void)
{   
    HAL_IWDG_Refresh(&IWDG_Handle); 	//喂狗
}
