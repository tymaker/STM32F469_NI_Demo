/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    20-11-2016
  * @brief   This example FMC SDRAM Demo
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

FATFS RAMDISKFatFs;  /* File system object for RAM disk logical drive */
FIL MyFile;          /* File object */
char RAMDISKPath[4]; /* RAM disk logical drive path */


extern UART_HandleTypeDef huart3;
extern uint8_t aRxBuffer[4];

/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */


static void SystemClock_Config(void);

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
		GPIO_Init_Structure.Pull  = GPIO_PULLDOWN; /* 设置下拉电阻 */
		GPIO_Init_Structure.Speed = GPIO_SPEED_HIGH;
		HAL_GPIO_Init(GPIOA, &GPIO_Init_Structure);
		
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOK, GPIO_PIN_3, GPIO_PIN_SET);

}


int main(void)
{
  FRESULT res;                                          /* FatFs function common result code */
  uint32_t byteswritten, bytesread;                     /* File write/read counts */
  uint8_t wtext[] = "This is STM32 working with FatFs"; /* File write buffer */
  uint8_t rtext[100];                                   /* File read buffer */

	//uint16_t *pdata_test;
	uint16_t read_temp;
  /* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch, instruction and Data caches
       - Systick timer is configured by default as source of time base, but user 
         can eventually implement his proper time base source (a general purpose 
         timer for example or other time source), keeping in mind that Time base 
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization: global MSP (MCU Support Package) initialization
     */
  HAL_Init();
  /* Configure the system clock to 180 MHz */
  SystemClock_Config();
	/* Initialize the SDRAM controller */
	HAL_SDRAM_Init_Conf();
  /* Initialize all configured peripherals */
  MX_USART3_UART_Init();

	HAL_Delay(100);
	
	printf("Hello World!\n");
	
	Init_GPIO();
	
	//pdata_test = (uint16_t *)SDRAM_BANK_ADDR;
	//*pdata_test = 0xf5f5;
	
	*(__IO uint32_t*) (SDRAM_BANK_ADDR + WRITE_READ_ADDR + 4*1) = 0x1234;
	
	read_temp = *(uint16_t *)(SDRAM_BANK_ADDR + WRITE_READ_ADDR + 4);
	printf("SDRAM Example 0x%x\n",read_temp);
	
  /*##-1- Link the RAM disk I/O driver #######################################*/
  if(FATFS_LinkDriver(&SDRAMDISK_Driver, RAMDISKPath) == 0) 
  {
    /*##-2- Register the file system object to the FatFs module ##############*/
    if(f_mount(&RAMDISKFatFs, (TCHAR const*)RAMDISKPath, 0) != FR_OK)
    {
      /* FatFs Initialization Error */
      HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,GPIO_PIN_RESET);
    }
    else
    {
      /*##-3- Create a FAT file system (format) on the logical drive #########*/
      if(f_mkfs((TCHAR const*)RAMDISKPath, 0, 0) != FR_OK)
      {
        HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,GPIO_PIN_RESET);
      }
      else
      {
        /*##-4- Create and Open a new text file object with write access #####*/
        if(f_open(&MyFile, "STM32.TXT", FA_CREATE_ALWAYS | FA_WRITE) != FR_OK) 
        {
          /* 'STM32.TXT' file Open for write Error */
          HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,GPIO_PIN_RESET);
        }
        else
        {
          /*##-5- Write data to the text file ################################*/
          res = f_write(&MyFile, wtext, sizeof(wtext), (void *)&byteswritten);
          
          if((byteswritten == 0) || (res != FR_OK))
          {
            /* 'STM32.TXT' file Write or EOF Error */
            HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,GPIO_PIN_RESET);
          }
          else
          {
            /*##-6- Close the open text file #################################*/
            f_close(&MyFile);
            
            /*##-7- Open the text file object with read access ###############*/
            if(f_open(&MyFile, "STM32.TXT", FA_READ) != FR_OK)
            {
              /* 'STM32.TXT' file Open for read Error */
              HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,GPIO_PIN_RESET);
            }
            else
            {
              /*##-8- Read data from the text file ###########################*/
              res = f_read(&MyFile, rtext, sizeof(rtext), (UINT*)&bytesread);
              
              if((bytesread == 0) || (res != FR_OK)) /* EOF or Error */
              {
                /* 'STM32.TXT' file Read or EOF Error */
                HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,GPIO_PIN_RESET);
              }
              else
              {
                /*##-9- Close the open text file #############################*/
                f_close(&MyFile);
                
                /*##-10- Compare read data with the expected data ############*/
                if ((bytesread != byteswritten))
                {                
                  /* Read data is different from the expected data */
                  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,GPIO_PIN_RESET);
                }
                else
                {
                  /* Success of the demo: no error occurrence */
                  HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_RESET);
                }
              }
            }
          }
        }
				if(f_open(&MyFile, "aa.txt", FA_CREATE_ALWAYS | FA_WRITE) == FR_OK)
					printf("Create aa.txt Ok\n");

        res = f_write(&MyFile, "Hello-World\n", sizeof(12), (void *)&byteswritten);
				
				f_close(&MyFile);
				
				f_open(&MyFile, "aa.txt", FA_READ);

				f_read(&MyFile, rtext, sizeof(rtext), (UINT*)&bytesread);
				
				printf("%s\n",rtext);
      }
    }
  }
  /*##-11- Unlink the RAM disk I/O driver ####################################*/
  FATFS_UnLinkDriver(RAMDISKPath);
	
	/* Infinite loop */
  while (1)
  {

  }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            PLL_R                          = 6
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_StatusTypeDef ret = HAL_OK;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
#if defined(USE_STM32469I_DISCO_REVA)
  RCC_OscInitStruct.PLL.PLLM = 25;
#else
  RCC_OscInitStruct.PLL.PLLM = 8;
#endif /* USE_STM32469I_DISCO_REVA */
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  RCC_OscInitStruct.PLL.PLLR = 6;
  
  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
  
  /* Activate the OverDrive to reach the 180 MHz Frequency */  
  ret = HAL_PWREx_EnableOverDrive();
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  
  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
}



#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
