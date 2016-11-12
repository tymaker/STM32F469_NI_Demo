/**
  ******************************************************************************
  * @file    stm32f4xx_Usart.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    12-11-2016
  * @brief   Usart.h
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
	
#ifndef __STM32F4XX_USART_H
#define __STM32F4XX_USART_H


/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_hal.h"


#define USARTx_FORCE_RESET()             __HAL_RCC_USART6_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART6_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_6
#define USARTx_TX_GPIO_PORT              GPIOC
#define USARTx_TX_AF                     GPIO_AF8_USART6
#define USARTx_RX_PIN                    GPIO_PIN_7
#define USARTx_RX_GPIO_PORT              GPIOC
#define USARTx_RX_AF                     GPIO_AF8_USART6

/* Definition for USARTx's NVIC */
#define USARTx_IRQn                      USART6_IRQn
#define USARTx_IRQHandler                USART6_IRQHandler

/* Size of Trasmission buffer */
#define TXBUFFERSIZE                      (COUNTOF(aTxBuffer) - 1)
/* Size of Reception buffer */
#define RXBUFFERSIZE                      TXBUFFERSIZE
  
/* Exported macro ------------------------------------------------------------*/
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
/* Exported functions ------------------------------------------------------- */


#define TRANSMITTER_BOARD

void Init_Usart6(void);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle);
void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle);
void HAL_UART_MspInit(UART_HandleTypeDef *huart);
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart);

#endif /* __STM32F4XX_USART_H */


