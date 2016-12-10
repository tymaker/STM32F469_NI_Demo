/**
  ******************************************************************************
  * @file    
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
	
#include "stm32f4xx_hal.h"

void MY_ADC_Init(void);
uint16_t Get_Adc(uint32_t ch);
uint16_t Get_Adc_Average(uint32_t ch,uint8_t times);
short Get_Temprate(void);

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

