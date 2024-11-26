#include "main.h"
extern uint32_t SystemCoreClock;
uint32_t systemClcok;

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

int main(void)
{
	RCC_Config();
	SystemCoreClockUpdate();
	systemClcok = SystemCoreClock;

  while (1)
  {

  }

}

void Error_Handler(void)
{

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
