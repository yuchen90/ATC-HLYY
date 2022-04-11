#include "main.h"
#include "declaration.h"

void TIM2_Error_Handler(void);

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
	TIM2_Handle.Instance = TIM2;                                             	//ͨ�ö�ʱ��2
	TIM2_Handle.Init.Prescaler = psc;                                        	//��Ƶϵ��
	TIM2_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;                       	//����ģʽ ����
	TIM2_Handle.Init.Period = arr;                                          	//�Զ���װֵ
	TIM2_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TIM2_Handle.Init.RepetitionCounter = 0u;
	TIM2_Handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  
  #if TIM2_EN
	if(HAL_TIM_Base_Init(&TIM2_Handle) != HAL_OK)
	    TIM2_Error_Handler();

	if(HAL_TIM_Base_Start_IT(&TIM2_Handle) != HAL_OK)    						//ʹ�ܶ�ʱ��2�Ͷ�ʱ��2�����жϣ�TIM_IT_UPDATE
	    TIM2_Error_Handler();
  #endif
}

/**
  * @brief  ��ʱ���жϷ���������,�ص�����
  * @param  htim : TIM handle ��HAL_TIM_IRQHandler()ʵ�δ���
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
        if(System_Time_Fg%80 < 41u)     //Ϊʲô��%80<41u
	        Y_FLASH_ENABLE=ON;
        else
            Y_FLASH_ENABLE=OFF;
    }    
  }
}

/**
  * @brief  TIM2��ʼ��������MCU_RUN����
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
