/**
  ******************************************************************************
  * @file    
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    
  * @brief   
  ******************************************************************************
  * @attention
  *
  */
	
#ifndef _STM32F4XX_HAL_MSP
#define _STM32F4XX_HAL_MSP

#include "stm32f4xx_hal.h"


#define STLK_RX_Pin GPIO_PIN_10
#define STLK_TX_Pin GPIO_PIN_11


void HAL_MspInit(void);
void MX_USART3_UART_Init(void);
void HAL_UART_MspInit(UART_HandleTypeDef* huart);
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle);

#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
