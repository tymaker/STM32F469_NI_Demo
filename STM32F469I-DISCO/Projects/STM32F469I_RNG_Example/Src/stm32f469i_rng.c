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

#include "stm32f469i_rng.h"


RNG_HandleTypeDef RNG_Handler;  //RNG句柄

//初始化RNG
uint8_t RNG_Init(void)
{
    uint16_t retry=0;
    
    RNG_Handler.Instance=RNG;
    HAL_RNG_Init(&RNG_Handler);//初始化RNG
    while(__HAL_RNG_GET_FLAG(&RNG_Handler,RNG_FLAG_DRDY)==RESET&&retry<10000)//等待RNG准备就绪
    {
        retry++;
        HAL_Delay(10);
    }
    if(retry>=10000) return 1;//随机数产生器工作不正常
    return 0;
}
void HAL_RNG_MspInit(RNG_HandleTypeDef *hrng)
{
     __HAL_RCC_RNG_CLK_ENABLE();//使能RNG时钟
}

//得到随机数
//返回值:获取到的随机数
uint32_t RNG_Get_RandomNum(void)
{
    return HAL_RNG_GetRandomNumber(&RNG_Handler);
}

//生成[min,max]范围的随机数
int RNG_Get_RandomRange(int min,int max)
{ 
   return HAL_RNG_GetRandomNumber(&RNG_Handler)%(max-min+1) +min;
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
