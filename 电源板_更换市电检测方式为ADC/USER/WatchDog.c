////////////////////////////////////////////////////////////////
/*
ι��
*/
////////////////////////////////////////////////////////////////
#include "stm32f10x.h"

	#include <stdio.h>
	
#include "common.h"
#include "data.h"




void WatchDog_int(uint16_t Settime_ms)// �������Ź�IWDG����
{
     /* Enable write access to IWDG_PR and IWDG_RLR registers */
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
   /* IWDG counter clock: 32KHz(LSI) / 32 = 1KHz */
  IWDG_SetPrescaler(IWDG_Prescaler_32); //�������Ź�Ԥ��ƵΪ32

   /* Set counter reload value to 1000 */
  IWDG_SetReload(Settime_ms);//����IWDG��װ��ֵ ��ΧΪ 0~0x0FFF;

    /* Reload IWDG counter */
  IWDG_ReloadCounter();//������װ�صļĴ�����ֵ����װ��IWDG������

    /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
  IWDG_Enable();//ʹ�� �������Ź�
}

