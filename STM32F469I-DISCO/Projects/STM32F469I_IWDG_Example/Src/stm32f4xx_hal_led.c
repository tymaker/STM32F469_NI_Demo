/**
  ******************************************************************************
  * @file    GPIO/GPIO_EXTI/Src/main.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    14-August-2015
  * @brief   This example describes how to configure and use GPIOs through
  *          the STM32F4xx HAL API.
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
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
	
	
#include "stm32f4xx_hal_led.h"


/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
	
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
		GPIO_Init_Structure.Pull  = GPIO_PULLDOWN; 
		GPIO_Init_Structure.Speed = GPIO_SPEED_HIGH;
		HAL_GPIO_Init(GPIOA, &GPIO_Init_Structure);
		
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOK, GPIO_PIN_3, GPIO_PIN_SET);

}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
