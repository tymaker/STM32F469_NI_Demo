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
	*/
	
	
#include "stm32f4xx_Iwdg.h"


IWDG_HandleTypeDef IwdgHandle;
static __IO uint32_t uwLsiFreq = 0;


void Init_Iwdg_Config(void){
  if (__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST) != RESET)
  {
    /* IWDGRST flag set: Turn LED1 on */
    /* Clear reset flags */
    __HAL_RCC_CLEAR_RESET_FLAGS();
  }
	
  /*##-3- Configure the IWDG peripheral ######################################*/
  /* Set counter reload value to obtain 250ms IWDG TimeOut.
     IWDG counter clock Frequency = LsiFreq / 32
     Counter Reload Value = 250ms / IWDG counter clock period
                          = 0.25s / (32/LsiFreq)
                          = LsiFreq / (32 * 4)
                          = LsiFreq / 128 */
  IwdgHandle.Instance = IWDG;

  IwdgHandle.Init.Prescaler = IWDG_PRESCALER_4;//IWDG_PRESCALER_32;
  IwdgHandle.Init.Reload    = 4095;

  if (HAL_IWDG_Init(&IwdgHandle) != HAL_OK)
  {
    /* Initialization Error */
    //Error_Handler();
  }

  /*##-4- Start the IWDG #####################################################*/
  if (HAL_IWDG_Start(&IwdgHandle) != HAL_OK)
  {
    //Error_Handler();
  }

}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
