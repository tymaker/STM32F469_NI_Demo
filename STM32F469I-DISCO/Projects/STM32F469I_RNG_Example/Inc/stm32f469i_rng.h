/**
  ******************************************************************************
  * @file    
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    22-11-2016
  * @brief   This example describes how to configure and use GPIOs through
  *          the STM32F4xx HAL API.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

#ifndef __STM32F469I_RNG
#define __STM32F469I_RNG

#include "stm32f4xx_hal.h"


uint8_t  RNG_Init(void);			//RNG初始化 
uint32_t RNG_Get_RandomNum(void);//得到随机数
int RNG_Get_RandomRange(int min,int max);//生成[min,max]范围的随机数




#endif /* stm32f469i_rng */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
