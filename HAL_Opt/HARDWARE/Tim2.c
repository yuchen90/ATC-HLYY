//��ʱ�������ڵ��ʱ���ʱ
#include "main.h"
#include "declaration.h"

TIM_HandleTypeDef TIM2_Handler;
void Error_Handle(void);

/**
  * @brief  TIMW2��Ӧ���蹦�ܳ�ʼ��
  * @param  reload���Զ���װֵ
  * @param  psc��ʱ��Ԥ��Ƶ��
  * ��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
  * Ft=��ʱ������Ƶ��,��λ:Mhz
  * @retval None
  */
void TIM2_Init(uint16_t arr,uint16_t psc)
{
  TIM2_Handler.Instance = TIMx;                                             //ͨ�ö�ʱ��2
  TIM2_Handler.Init.Prescaler = psc;                                        //��Ƶϵ��
  TIM2_Handler.Init.CounterMode = TIM_COUNTERMODE_UP;                       //����ģʽ ����
  TIM2_Handler.Init.Period = arr;                                        //�Զ���װֵ
  TIM2_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  TIM2_Handler.Init.RepetitionCounter = 0u;
  TIM2_Handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  
  if(HAL_TIM_Base_Init(&TIM2_Handler) != HAL_OK)
  Error_Handle();

  if(HAL_TIM_Base_Start_IT(&TIM2_Handler) != HAL_OK)    //ʹ�ܶ�ʱ��2�Ͷ�ʱ��2�����жϣ�TIM_IT_UPDATE
  Error_Handle();
}

/**
  * @brief  ��ʱ���жϷ���������,�ص�����
  * @param  htim : TIM handle ��HAL_TIM_IRQHandler()ʵ�δ���
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==(&TIM2_Handler))
    {
      Timer_Fg++;
			Timer_Fg1++;
			if(Timer_Fg >= 30000) //��������û�20000
			{
				Timer_Fg = 20000;
			}
			if(Timer_Fg1 >= 30000)
			{
				Timer_Fg1 = 20000;
			}
			
			VACheck_Fg = 0u;
    }
}

void Error_Handle(void)
{
  while(1)
  {
  }

}
