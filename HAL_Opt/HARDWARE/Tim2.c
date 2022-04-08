//计时器，用于点灯时间计时
#include "main.h"
#include "declaration.h"

void TIM_Error_Handle(void);

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
  TIM2_Handle.Instance = TIM2;                                             //通用定时器2
  TIM2_Handle.Init.Prescaler = psc;                                        //分频系数
  TIM2_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;                       //计数模式 向上
  TIM2_Handle.Init.Period = arr;                                           //自动重装值
  TIM2_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  TIM2_Handle.Init.RepetitionCounter = 0u;
  TIM2_Handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  
  if(HAL_TIM_Base_Init(&TIM2_Handle) != HAL_OK)
  TIM_Error_Handle();

  if(HAL_TIM_Base_Start_IT(&TIM2_Handle) != HAL_OK)    //使能定时器2和定时器2更新中断：TIM_IT_UPDATE
  TIM_Error_Handle();
}

/**
  * @brief  定时器中断服务函数调用,回调函数
  * @param  htim : TIM handle 由HAL_TIM_IRQHandler()实参传递
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==(&TIM2_Handle))
    {
      Sytem_Timer_Fg++;
			Sytem_Timer_Fg1++;
			if(Sytem_Timer_Fg >= 30000) //半秒后重置回20000
			{
				Sytem_Timer_Fg = 20000;
			}
			if(Sytem_Timer_Fg1 >= 30000)
			{
				Sytem_Timer_Fg1 = 20000;
			}
			VACheck_Fg=0u;
    }
}

void TIM_Error_Handle(void)
{
  while(1)
  {
    MCU_RUN = LED_ON;
  }
}
