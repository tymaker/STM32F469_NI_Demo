/**
  ******************************************************************************
  * @file    stm32f4xx_wwdg_msp.c
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

#include "stm32f4xx_wwdg_msp.h"

WWDG_HandleTypeDef WWDG_Handler;     //窗口看门狗句柄

//保存WWDG计数器的设置值，默认为最大
uint8_t WWDG_CNT=0X7F;


/**
  * @brief  This function Init WWDG
  * @param  None
  * @retval None
	* tr    :T[6:0]计数器值
	* wr    :W[6:0]窗口值
	* fprer :分频系数(WDGTB)
	* fwwdg=PCLK1/(4096*2^fprer). 一般PCLK1=45Mhz
  */
void MX_WWDG_Init(uint8_t tr,uint8_t wr,uint32_t fprer)
{
    WWDG_Handler.Instance=WWDG;
    WWDG_Handler.Init.Prescaler=fprer;   //设置分频系数
    WWDG_Handler.Init.Window=wr;         //设置窗口值
    WWDG_Handler.Init.Counter=tr;        //设置计数器值
    HAL_WWDG_Init(&WWDG_Handler);        //初始化WWDG
    HAL_WWDG_Start_IT(&WWDG_Handler);    //开启窗口看门狗  
}


/**
  * @}
  */
void HAL_WWDG_MspInit(WWDG_HandleTypeDef *hwwdg)
{   
    __HAL_RCC_WWDG_CLK_ENABLE();    //使能窗口看门狗时钟
        
    HAL_NVIC_SetPriority(WWDG_IRQn,2,3);    //抢占优先级2，子优先级为3
    HAL_NVIC_EnableIRQ(WWDG_IRQn);          //使能窗口看门狗中断
}

/**
  * @}
  * 中断服务函数处理过程
  * 此函数会被HAL_WWDG_IRQHandler()调用
  */
void HAL_WWDG_WakeupCallback(WWDG_HandleTypeDef* hwwdg)
{
    HAL_WWDG_Refresh(&WWDG_Handler,WWDG_CNT);//更新窗口看门狗值
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_RESET);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
