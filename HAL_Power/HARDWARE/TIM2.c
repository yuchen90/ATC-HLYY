#include "main.h"
#include "declaration.h"

TIM_HandleTypeDef TIM2_Handle;
void Error_Handler(void);

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
	TIM2_Handle.Instance = TIMx;                                             	//ͨ�ö�ʱ��2
	TIM2_Handle.Init.Prescaler = psc;                                        	//��Ƶϵ��
	TIM2_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;                       	//����ģʽ ����
	TIM2_Handle.Init.Period = arr;                                          	//�Զ���װֵ
	TIM2_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TIM2_Handle.Init.RepetitionCounter = 0u;
	TIM2_Handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  
	if(HAL_TIM_Base_Init(&TIM2_Handle) != HAL_OK)
	Error_Handler();

	if(HAL_TIM_Base_Start_IT(&TIM2_Handle) != HAL_OK)    						//ʹ�ܶ�ʱ��2�Ͷ�ʱ��2�����жϣ�TIM_IT_UPDATE
	Error_Handler();
}

/**
  * @brief  ��ʱ���жϷ���������,�ص�����
  * @param  htim : TIM handle ��HAL_TIM_IRQHandler()ʵ�δ���
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==(&TIM2_Handle))
    {

    }
}

void Error_Handler(void)
{
	while(1)
	{
	}
}
