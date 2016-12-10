/**
  ******************************************************************************
  * @file    IAP/IAP_USART/main.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    12-07-2016
  * @brief   This example describes how to configure and use GPIOs through
  *          the STM32F4xx HAL API.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

extern UART_HandleTypeDef huart3;
extern uint8_t aRxBuffer[4];

extern uint16_t USART_RX_STA;
extern uint32_t USART_RX_CNT;
extern uint8_t USART_RX_BUF[USART_REC_LEN] __attribute__ ((at(0X20001000)));

uint8_t Key_Value = 1;

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);


/**
  * @brief EXTI line detection callbacks
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == GPIO_PIN_0)
  {
    /* Toggle LED1 */
		Key_Value  = ~Key_Value;
		/* Check the parameters */
		GPIOK->ODR ^= GPIO_PIN_3;
  }
}


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
		//GPIO_Init_Structure.Mode  = GPIO_MODE_INPUT;
    /* Configure PA.00 pin as input floating */
    GPIO_Init_Structure.Mode = GPIO_MODE_IT_RISING;
    GPIO_Init_Structure.Pull  = GPIO_PULLDOWN; /* 设置下拉电阻 */
		GPIO_Init_Structure.Speed = GPIO_SPEED_HIGH;
		HAL_GPIO_Init(GPIOA, &GPIO_Init_Structure);
		
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOK, GPIO_PIN_3, GPIO_PIN_SET);

		HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
		HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}


int main(void)
{
		uint8_t t;
		uint16_t oldcount=0;				    //老的串口接收数据值
		uint32_t applenth=0;				    //接收到的app代码长度
		uint8_t clearflag=0; 

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

  /* Infinite loop */
	Init_GPIO();
	
  /* Initialize all configured peripherals */
  MX_USART3_UART_Init();

	HAL_Delay(100);
	
	printf("Hello World!\n");
  
	
	while (1)
  {
	 	if(USART_RX_CNT)
		{
			if(oldcount==USART_RX_CNT)//新周期内,没有收到任何数据,认为本次数据接收完成.
			{
				applenth=USART_RX_CNT;
				oldcount=0;
				USART_RX_CNT=0;
				printf("用户程序接收完成!\r\n");
				printf("代码长度:%dBytes\r\n",applenth);
			}else oldcount=USART_RX_CNT;			
		}
		t++;
		HAL_Delay(10);
		if(t==30)
		{
			//LED0=!LED0;
			t=0;
			if(clearflag)
			{
				clearflag--;
			}
		}
		//key=KEY_Scan(0);
		if(Key_Value == 0)	//WK_UP按键按下
		{
			if(applenth)
			{
				printf("开始更新固件...\n");	
				printf("Copying APP2FLASH...\n");
 				if(((*(uint32_t*)(0X20001000+4))&0xFF000000)==0x08000000)//判断是否为0X08XXXXXX.
				{	 
					iap_write_appbin(FLASH_APP1_ADDR,USART_RX_BUF,applenth);//更新FLASH代码   
					printf("Copy APP Successed!!");
					printf("固件更新完成!\r\n");	
				}else 
				{
					printf("Illegal FLASH APP!  ");	   
					printf("非FLASH应用程序!\r\n");
				}
 			}else 
			{
				printf("没有可以更新的固件!\r\n");
				printf("No APP!");
			}
			clearflag=7;//标志更新了显示,并且设置7*300ms后清除显示									 
		}
		/*if(Key_Value==0)	//KEY1按下
		{
			if(applenth)
			{																	 
				printf("固件清除完成!\r\n");    
				LCD_ShowString(30,210,200,16,16,"APP Erase Successed!");
				applenth=0;
			}else 
			{
				printf("没有可以清除的固件!\r\n");
			}
			clearflag=7;//标志更新了显示,并且设置7*300ms后清除显示									 
		}
		*/
		if(Key_Value==1)	//KEY2按下
		{
			printf("开始执行FLASH用户代码!!\r\n");
			if(((*(uint32_t*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//判断是否为0X08XXXXXX.
			{	 
				iap_load_app(FLASH_APP1_ADDR);//执行FLASH APP代码
			}else 
			{
				printf("非FLASH应用程序,无法执行!\r\n");
				printf("Illegal FLASH APP!");	   
			}									 
			clearflag=7;//标志更新了显示,并且设置7*300ms后清除显示	  
		}
		/*if(key==KEY0_PRES)	//KEY0按下
		{
			printf("开始执行SRAM用户代码!!\r\n");
			if(((*(vu32*)(0X20001000+4))&0xFF000000)==0x20000000)//判断是否为0X20XXXXXX.
			{	 
				iap_load_app(0X20001000);//SRAM地址
			}else 
			{
				printf("非SRAM应用程序,无法执行!\r\n");
				LCD_ShowString(30,210,200,16,16,"Illegal SRAM APP!");	   
			}									 
			clearflag=7;//标志更新了显示,并且设置7*300ms后清除显示	 
		}
		*/
		
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
