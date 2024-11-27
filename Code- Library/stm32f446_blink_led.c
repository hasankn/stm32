#include "main.h"

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

void GPIO_Config()
{
	RCC -> AHB1ENR |=   (1 << 0);			// GPIOA CLOCK ENABLE
	GPIOA -> MODER |=   (0x1 << 10);		// GPIOA 5.PIN OUTPUT
	GPIOA -> MODER &=  ~(0x1 << 11);
	GPIOA -> OSPEEDR |= (3 << 10);			// GPIOA SPEED IS HIGH SPEED
}

int main(void)
{
	RCC_Config();
	GPIO_Config();
  while (1)
  {
	  GPIOA -> ODR |= (1 << 5);				// GPIOA HATTININ 5. PİNİNİ OUTPUT YAPMA
	  for (int i =0; i < 1800000; i++);
	  GPIOA -> ODR &= ~(1 <<5);
	  for (int i =0; i < 1800000; i++);
  }

}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};


  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);


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

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
 
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{

}
#endif /* USE_FULL_ASSERT */
