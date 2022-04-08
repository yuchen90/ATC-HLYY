/**
  ******************************************************************************
  * @file    Templates/Src/stm32f1xx_hal_msp.c
  * @author  MCD Application Team
  * @brief   HAL MSP module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/**
  * @brief CAN MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  *           - NVIC configuration for DMA interrupt request enable
  * @param hcan: CAN handle pointer
  * @retval None
  */
void HAL_CAN_MspInit(CAN_HandleTypeDef *hcan)
{
    GPIO_InitTypeDef GPIO_Init;

  // Enable CAN1 & GPIOA CLK
  CAN1_CLK_ENABLE();
  CAN1_GPIO_CLK_ENABLE();

  //PA11 Rx
  GPIO_Init.Pin=CAN1_Rx_PIN;
  GPIO_Init.Mode=GPIO_MODE_INPUT;
  GPIO_Init.Pull=GPIO_PULLUP;
  HAL_GPIO_Init(CAN1_Rx_GPIO_PORT,&GPIO_Init);

  //PA12 Tx
  GPIO_Init.Pin=CAN1_Tx_PIN;
  GPIO_Init.Mode=GPIO_MODE_AF_PP;
  GPIO_Init.Speed=GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(CAN1_Tx_GPIO_PORT,&GPIO_Init); 

  //CAN1 Rx Interrupt Init
  HAL_NVIC_SetPriority(CAN1_Rx_IRQn,1,2);         //抢占优先级：1 
  HAL_NVIC_EnableIRQ(CAN1_Rx_IRQn);
}

/**
  * @brief CAN MSP De-Initialization
  *          - Disable the Peripheral's clock
  *          - Revert GPIO to their default state
  * @param hcan: CAN handle pointer
  * @retval None
  */
void HAL_CAN_MspDeInit(CAN_HandleTypeDef *hcan)
{
  // 重置,释放外设
  CAN1_FORCE_RESET();
  CAN1_RELEASE_RESET();

  // 失能外设时钟
  HAL_GPIO_DeInit(CAN1_Tx_GPIO_PORT, CAN1_Tx_PIN);
  HAL_GPIO_DeInit(CAN1_Rx_GPIO_PORT, CAN1_Rx_PIN);

  // 失能中断
  HAL_NVIC_DisableIRQ(USB_LP_CAN1_RX0_IRQn);
}

/**
  * @brief TIM MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  * @param htim: TIM handle pointer
  * 定时器底册驱动，开启时钟，设置中断优先级
  * @retval None
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM2)                      //确认开启时钟为TIM2
	{
		TIM2_CLK_ENABLE();                              //使能TIM2时钟
		HAL_NVIC_SetPriority(TIM2_IRQn,0,0);            //设置中断优先级，抢占优先级0，子优先级0
		HAL_NVIC_EnableIRQ(TIM2_IRQn);                  //开启ITM2中断   
	}
}

/**
  * @brief  DeInitializes TIM Base MSP.
  * @param  htim TIM Base handle
  * @retval None
  */
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim)
{
  TIM2_FORCE_RESET();
  TIM2_RELEASE_RESET();

  HAL_NVIC_DisableIRQ(TIM2_IRQn);
}
