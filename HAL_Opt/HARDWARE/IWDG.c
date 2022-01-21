#include "main.h"
#include "declaration.h"

IWDG_HandleTypeDef IWDG_Handler;    //�������Ź����

/**
  * @brief  ��ʼ���������Ź�
  * @param  pre����Ƶ��:IWDG_PRESCALER_4~IWDG_PRESCALER_256
  * @param  reload���Զ���װ��ֵ,0~0XFFF.
  * ʱ�����(���):Tout=((4*2^prer)*rlr)/32 (ms).
  * @retval None
  */
void IWDG_Init(uint8_t pre,uint_fast16_t reload)
{
    IWDG_Handler.Instance=IWDG;
    IWDG_Handler.Init.Prescaler=pre;	//����IWDG��Ƶϵ��
    IWDG_Handler.Init.Reload=reload;	//��װ��ֵ
    HAL_IWDG_Init(&IWDG_Handler);		//��ʼ��IWDG,Ĭ�ϻῪ���������Ź�
}

/**
  * @brief  ι�������Ź�
  * @param  None
  * @retval None
  */
void IWDG_Feed(void)
{   
    HAL_IWDG_Refresh(&IWDG_Handler); 	//ι��
}
