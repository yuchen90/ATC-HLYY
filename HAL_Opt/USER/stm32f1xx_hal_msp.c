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
  __HAL_RCC_CAN1_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  //PA11 Rx
  GPIO_Init.Pin = CANx_RX_PIN;
  GPIO_Init.Mode = GPIO_MODE_INPUT;
  GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;
  // GPIO_Init.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(CANx_TX_GPIO_PORT,&GPIO_Init);

  //PA12 Tx
  GPIO_Init.Pin = CANx_TX_PIN;
  GPIO_Init.Mode = GPIO_MODE_AF_PP;
  GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;
  // GPIO_Init.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(CANx_TX_GPIO_PORT,&GPIO_Init); 

  //CAN1 Rx Interrupt Init
  HAL_NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn,1,0); //抢占优先级：1 
  HAL_NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
}

/**
  * @brief CAN MSP De-Initialization
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO to their default state
  * @param hcan: CAN handle pointer
  * @retval None
  */
void HAL_CAN_MspDeInit(CAN_HandleTypeDef *hcan)
{
  // 重置外设
  __HAL_RCC_CAN1_FORCE_RESET();
  __HAL_RCC_CAN1_RELEASE_RESET();

  // 失能外设时钟
  HAL_GPIO_DeInit(CANx_TX_GPIO_PORT, CANx_TX_PIN);
  HAL_GPIO_DeInit(CANx_RX_GPIO_PORT, CANx_RX_PIN);

  // 失能中断
  HAL_NVIC_DisableIRQ(USB_LP_CAN1_RX0_IRQn);
}
