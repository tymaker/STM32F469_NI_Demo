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

/* Includes ------------------------------------------------------------------*/

#ifndef __STM32F469I_RTC_TEMPLATE
#define __STM32F469I_RTC_TEMPLATE

#include "stm32f4xx_hal.h"



HAL_StatusTypeDef RTC_Set_Time(uint8_t hour,uint8_t min,uint8_t sec,uint8_t ampm);      //RTC时间设置
HAL_StatusTypeDef RTC_Set_Date(uint8_t year,uint8_t month,uint8_t date,uint8_t week);	  //RTC日期设置
uint8_t stm32f4xx_RTC_Init_Config(void);
void HAL_RTC_MspInit(RTC_HandleTypeDef* hrtc);

void RTC_Set_AlarmA(uint8_t week,uint8_t hour,uint8_t min,uint8_t sec); //设置闹钟时间(按星期闹铃,24小时制)
void RTC_Set_WakeUp(uint32_t wksel,uint16_t cnt);                       //周期性唤醒定时器设置

void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc);

#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
