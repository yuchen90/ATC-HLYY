////////////////////////////////////////////////////////////////
/*
定时器2初始化
*/
////////////////////////////////////////////////////////////////
#include "stm32f10x.h"
#include "common.h"
#include "data.h"



//初始化TIM2定时器及中断
//每次进入中断服务程序间隔时间为
//((1+arr )/72M)*(1+psc )=((1+1999)/72M)*(1+35999)=1秒
void TIM2_Config(u16 arr,u16 psc)
{
    //定时器时间是1s

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    //清除中断标志位
    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//TIM_ClearFlag(TIM2,TIM_FLAG_Update);//两者作用相同

    //自动装载的周期值0-0xffff，72M/36000=2000
    TIM_TimeBaseStructure.TIM_Period = arr;
    //时钟除数预分频值0-oxffff，下面是36000分频
    TIM_TimeBaseStructure.TIM_Prescaler = psc;
    ////普通和高级才有下面两行
    //时钟分割，暂时为0，高级应用才用
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    //计数模式，向上下，中央对齐123
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);

    //开启中断
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    //开启外设
    TIM_Cmd(TIM2,ENABLE);
		
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
		
}



//--------------------stm32f10x_it.c------------------------
//中断函数中自己编写
uint8_t timerfgten;
void TIM2_IRQHandler(void)
{
    //判断TIM3更新中断是否发生
    if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
    {
        //必须清楚标志位
				TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
			//状态取反
	//		timerfgten++;
	//		if(timerfgten>=10)
			{
		//		timerfgten=0;
			timerfg++;
			if(timerfg>=25000)
			{
				timerfg=15000;
			}
			timerfg1++;
			if(timerfg1>=20000)
			{
				timerfg1=10000;
			}
			
			if(((timerfg<15000)||((TakeOverNumbuse>0)&&(TakeOverorder==1)))&&(Y_FLASHorder==0))
			{
				if(timerfg1%80<41)
				{
					Y_FLASH(SON);
				}
				else// if(timerfg1%100==0)
				{
					Y_FLASH(SOFF);
				}
			}
			

    }

	}
}



