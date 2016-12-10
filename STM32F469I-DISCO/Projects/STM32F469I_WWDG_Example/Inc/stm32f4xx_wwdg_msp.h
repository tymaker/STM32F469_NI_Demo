/**
  ******************************************************************************
  * @file    stm32f4xx_wwdg_msp.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    
  * @brief   This example describes how to configure and use GPIOs through
  *          the STM32F4xx HAL API.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
	
#ifndef __STM32F4XX_WWDG_MSP
#define __STM32F4XX_WWDG_MSP


#include "stm32f4xx_hal.h"


void MX_WWDG_Init(uint8_t tr,uint8_t wr,uint32_t fprer);
void HAL_WWDG_MspInit(WWDG_HandleTypeDef *hwwdg);
void HAL_WWDG_WakeupCallback(WWDG_HandleTypeDef* hwwdg);

#endif /* stm32f4xx_wwdg_msp.h */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
