/**
  ******************************************************************************
  * @file    stm32f4xx_hal_Exit.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    14-22-2016
  * @brief   This example describes how to configure and use GPIOs through
  *          the STM32F4xx HAL API.
  ******************************************************************************
  * @attention
  *
	*/
#ifndef __STM32F4XX_HAL_EXIT
#define __STM32F4XX_HAL_EXIT

#include "stm32f4xx_hal.h"


void EXTI0_IRQHandler_Config(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);



#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
