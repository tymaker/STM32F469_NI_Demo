/**
  ******************************************************************************
  * @file    stm32f4xx_LED.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11-11-2016
  * @brief   This sample code shows how to use UART HAL API to transmit
  *          and receive a data buffer with a communication process based on
  *          IT transfer. 
  *          The communication is done using 2 Boards.
  ******************************************************************************
  * @attention
  *
	*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_LED.h"

void Init_GPIO(){
	
	  /********************
			LED1  PG6
			LED2	PD4
			LED3	PD5
			LED4	PK3
			KEY1  PA0
		*********************/
		GPIO_InitTypeDef GPIO_Init_Structure;
		/* Init GPIO Clock  */
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOG_CLK_ENABLE();
		__HAL_RCC_GPIOD_CLK_ENABLE();
		__HAL_RCC_GPIOK_CLK_ENABLE();
	  /* Init */
		GPIO_Init_Structure.Pin   = GPIO_PIN_6;
	  GPIO_Init_Structure.Mode  = GPIO_MODE_OUTPUT_PP;
	  GPIO_Init_Structure.Pull  = GPIO_PULLUP;
	  GPIO_Init_Structure.Speed = GPIO_SPEED_HIGH;
		HAL_GPIO_Init(GPIOG, &GPIO_Init_Structure);

		GPIO_Init_Structure.Pin   = GPIO_PIN_4 | GPIO_PIN_5;
	  GPIO_Init_Structure.Mode  = GPIO_MODE_OUTPUT_PP;
	  GPIO_Init_Structure.Pull  = GPIO_PULLUP;
	  GPIO_Init_Structure.Speed = GPIO_SPEED_HIGH;
		HAL_GPIO_Init(GPIOD, &GPIO_Init_Structure);
		
		GPIO_Init_Structure.Pin   = GPIO_PIN_3;
	  GPIO_Init_Structure.Mode  = GPIO_MODE_OUTPUT_PP;
	  GPIO_Init_Structure.Pull  = GPIO_PULLUP;
	  GPIO_Init_Structure.Speed = GPIO_SPEED_HIGH;
		HAL_GPIO_Init(GPIOK, &GPIO_Init_Structure);
		
		GPIO_Init_Structure.Pin   = GPIO_PIN_0;
		GPIO_Init_Structure.Mode  = GPIO_MODE_INPUT;
		GPIO_Init_Structure.Pull  = GPIO_PULLDOWN; /* 设置下拉电阻 */
		GPIO_Init_Structure.Speed = GPIO_SPEED_HIGH;
		HAL_GPIO_Init(GPIOA, &GPIO_Init_Structure);
		
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOK, GPIO_PIN_3, GPIO_PIN_SET);

}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
