#include "main.h"
#include "declaration.h"

void TIM2_Error_Handler(void);

/**
  * @brief  TIMW2对应外设功能初始化
  * @param  reload：自动重装值
  * @param  psc：时钟预分频数
  * 定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
  * Ft=定时器工作频率,单位:Mhz
  * @retval None
  */
void TIM2_Init(uint16_t arr,uint16_t psc)
{
	TIM2_Handle.Instance = TIM2;                                             	//通用定时器2
	TIM2_Handle.Init.Prescaler = psc;                                        	//分频系数
	TIM2_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;                       	//计数模式 向上
	TIM2_Handle.Init.Period = arr;                                          	//自动重装值
	TIM2_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TIM2_Handle.Init.RepetitionCounter = 0u;
	TIM2_Handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  
  #if TIM2_EN
	if(HAL_TIM_Base_Init(&TIM2_Handle) != HAL_OK)
	    TIM2_Error_Handler();

	if(HAL_TIM_Base_Start_IT(&TIM2_Handle) != HAL_OK)    						//使能定时器2和定时器2更新中断：TIM_IT_UPDATE
	    TIM2_Error_Handler();
  #endif
}

/**
  * @brief  定时器中断服务函数调用,回调函数
  * @param  htim : TIM handle 由HAL_TIM_IRQHandler()实参传递
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  // if(htim == (&TIM2_Handle))
  {
    System_Time_Fg++;
    if(System_Time_Fg >= 25000u)
        System_Time_Fg=15000u;
    
        System_Time_Fg1++;
    if(System_Time_Fg1 >= 20000u)
        System_Time_Fg1=10000u;
    
    if(((System_Time_Fg < 15000u) || (TakeOver_DataNum > 0u)) && (TakeOver_Enable == 1u) && (Y_FLASH_ENABLE == 0u))
    {
        if(System_Time_Fg%80 < 41u)     //为什么是%80<41u
	        Y_FLASH_ENABLE=ON;
        else
            Y_FLASH_ENABLE=OFF;
    }    
  }
}

/**
  * @brief  TIM2初始化，错误MCU_RUN常亮
  * @param  None
  * @retval None
  */
void TIM2_Error_Handler(void)
{
	while(1)
	{
        MCU_RUN=LED_ON;
	}
}
