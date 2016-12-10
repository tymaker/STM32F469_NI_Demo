/**
  ******************************************************************************
  * @file    GPIO/GPIO_EXTI/Inc/main.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    14-August-2015
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  */
	
#ifndef _STM32F4XX_HAL_MSP
#define _STM32F4XX_HAL_MSP

#include "stm32f4xx_hal.h"


#define STLK_RX_Pin GPIO_PIN_10
#define STLK_TX_Pin GPIO_PIN_11

#define USART_REC_LEN  			180*1024//定义最大接收字节数 180K
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收

void HAL_MspInit(void);
void MX_USART3_UART_Init(void);
void HAL_UART_MspInit(UART_HandleTypeDef* huart);
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle);

#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
