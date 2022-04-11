#include "main.h"
#include "declaration.h"

/**
  * @brief  ��ʼ��ϵͳʱ��
  * @param  pll����Ƶ����
  * @retval None
  */
void System_Clock_Init(uint32_t pll)
{
    HAL_StatusTypeDef ret = HAL_OK;
    RCC_OscInitTypeDef RCC_OscInitStructure; 
    RCC_ClkInitTypeDef RCC_ClkInitStructure;
    
    RCC_OscInitStructure.OscillatorType=RCC_OSCILLATORTYPE_HSE;    	  //ʱ��ԴΪHSE
    RCC_OscInitStructure.HSEState=RCC_HSE_ON;                      	  //��HSE
  	RCC_OscInitStructure.HSEPredivValue=RCC_HSE_PREDIV_DIV1;		      //HSEԤ��Ƶ
    RCC_OscInitStructure.PLL.PLLState=RCC_PLL_ON;					            //��pll
    RCC_OscInitStructure.PLL.PLLSource=RCC_PLLSOURCE_HSE;			        //pllʱ��Դѡ��HSE
    RCC_OscInitStructure.PLL.PLLMUL=pll; 							                //��pll��Ƶ����
    ret=HAL_RCC_OscConfig(&RCC_OscInitStructure);                     //��ʼ��
	
    if(ret!=HAL_OK) while(1);
    
    //ѡ��pll��Ϊϵͳʱ��Դ��������HCLK,PCLK1��PCLK2
    RCC_ClkInitStructure.ClockType=(RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStructure.SYSCLKSource=RCC_SYSCLKSOURCE_PLLCLK;		    //����ϵͳʱ��ʱ��ԴΪpll
    RCC_ClkInitStructure.AHBCLKDivider=RCC_SYSCLK_DIV1;				        //AHB��Ƶϵ��Ϊ1
    RCC_ClkInitStructure.APB1CLKDivider=RCC_HCLK_DIV2; 				        //APB1��Ƶϵ��Ϊ2
    RCC_ClkInitStructure.APB2CLKDivider=RCC_HCLK_DIV1; 				        //APB2��Ƶϵ��Ϊ1
    ret=HAL_RCC_ClockConfig(&RCC_ClkInitStructure,FLASH_LATENCY_2);	  //ͬʱ����FLASH��ʱ����Ϊ2WS��Ҳ����3��CPU���ڡ�(�����ϵͳʱ��Ƶ��ѡ��)
		
    if(ret!=HAL_OK) while(1);
}
