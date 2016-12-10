/**
  ******************************************************************************
  * @file    stm32f469_fmc_sdram.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    20-11-2016
  * @brief   
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
	
#ifndef __STM32F469_FMC_SDRAM
#define __STM32F469_FMC_SDRAM


#include "stm32f4xx_hal.h"

#define   SDRAM_OK         ((uint8_t)0x00)
#define   SDRAM_ERROR      ((uint8_t)0x01)

#define SDRAM_BANK_ADDR                 ((uint32_t)0xC0000000)
#define SDRAM_DEVICE_ADDR               ((uint32_t)0xC0000000)
#define WRITE_READ_ADDR     						((uint32_t)0x0800)
 #define SDRAM_DEVICE_SIZE  						((uint32_t)0x800000)
/* #define SDRAM_MEMORY_WIDTH              FMC_SDRAM_MEM_BUS_WIDTH_8  */
/* #define SDRAM_MEMORY_WIDTH              FMC_SDRAM_MEM_BUS_WIDTH_16 */
#define SDRAM_MEMORY_WIDTH              FMC_SDRAM_MEM_BUS_WIDTH_32

#define SDCLOCK_PERIOD                  FMC_SDRAM_CLOCK_PERIOD_2
/* #define SDCLOCK_PERIOD                  FMC_SDRAM_CLOCK_PERIOD_3 */

#define SDRAM_TIMEOUT     ((uint32_t)0xFFFF)

#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)


void HAL_SDRAM_Init_Conf(void);

void BSP_SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Command);

void HAL_SDRAM_MspInit(SDRAM_HandleTypeDef *hsdram);

void HAL_SDRAM_MspDeInit(SDRAM_HandleTypeDef *hsdram);

uint8_t BSP_SDRAM_ReadData(uint32_t uwStartAddress, uint32_t *pData, uint32_t uwDataSize);

uint8_t BSP_SDRAM_ReadData_DMA(uint32_t uwStartAddress, uint32_t *pData, uint32_t uwDataSize);

uint8_t BSP_SDRAM_WriteData(uint32_t uwStartAddress, uint32_t *pData, uint32_t uwDataSize);

uint8_t BSP_SDRAM_WriteData_DMA(uint32_t uwStartAddress, uint32_t *pData, uint32_t uwDataSize);

uint8_t BSP_SDRAM_Sendcmd(FMC_SDRAM_CommandTypeDef *SdramCmd);





#endif /* stm32f469_fmc_sdram */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
