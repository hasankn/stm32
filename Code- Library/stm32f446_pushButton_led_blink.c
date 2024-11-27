#include "main.h"

int count = 0;

void delay(uint32_t time)
{
	while(time--);
}

void SystemClock_Config(void);
//---------------------------------------------------------------
void RCC_Config(void)
{
	RCC -> CR |= (1 << 16);				// HSE on
	while(!(RCC->CR&(1 << 17)));		// HSE Ready

	RCC -> PLLCFGR = 0;					// PLL CFGR RESET
	RCC -> PLLCFGR |= (1 << 22);		// PLL = HSE
	RCC -> PLLCFGR |= (4 << 0);			// PLLM = 4
	RCC -> PLLCFGR |= (180 << 6);		// PLLN = 180
	RCC -> PLLCFGR |= (0 << 16);		// PLLP = 2

	RCC -> CR |= (1 << 24);				// PLL select
	while(!(RCC->CR & (1 << 25)));		// PLL ready


    FLASH->ACR |= (5 << 0);  			// 5 wait states
    /*
    FLASH->ACR |= (1 << 8);
    FLASH->ACR |= (1 << 9);
    FLASH->ACR |= (1 << 10);
     */
	RCC ->CFGR &= ~(3 << 0);			// System clock switch reset
	RCC ->CFGR |=  (2 << 0);			// System clock switch , PLL_P selected as system clock
	while ((RCC->CFGR & (0b11 << 2)) != (0b10 << 2));
}
//---------------------------------------------------------------

void GPIO_Confif()
{
	RCC  -> AHB1ENR  |= (5 << 0);    	// GPIOA VE GPIOC PORTLARININ
	GPIOA -> MODER   |=  (1 << 10);		// GPIOA PORTUNUN 5.PİNİNİN AKTİVE EDİLMESİ
	GPIOA -> MODER   &= ~(1 << 11);		// GPIOA PORTUNUN 5.PİNİNİN AKTİVE EDİLMESİ
	GPIOA -> OTYPER  = 0x00000000;		// OTYPER REGİSTERİNİN SIFIRLANMASI
	GPIOA -> OSPEEDR |=(3 << 10);		// SİSTEMİN HIZINI BELİRLENMESİ
	GPIOA -> PUPDR   &= ~(3 << 10);		// GPIOA PİNLERİNİN  No pull-up, pull-down MODUNUN SEÇİLMESİ
}



int main(void)
{


  HAL_Init();
  SystemClock_Config();

  RCC_Config();
  GPIO_Confif();
  while (1)
  {
	  if(GPIOC->IDR & (1 << 13))	//BUTONA BASILIP BASILMADĞININ KONTROL EDİLMESİ
	  {
		  while(GPIOC -> IDR & (1 << 13));
		  delay(1800000);
		  count++;
	  }
	  if (count % 2 == 0)
	  {
		  GPIOA -> ODR = 0x00000000;
	  }
	  else
	  {
		  GPIOA -> ODR |= (1 << 5);	//USER LEDİNİN ÇALIŞMASI
	  }

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
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
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
