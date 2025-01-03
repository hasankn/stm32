#include "stm32F446xx.h"

static 	void GPIO_LedConfig();


int main(void)
{
	GPIO_LedConfig();
	GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);

	for(;;);
}


static 	void GPIO_LedConfig()
{
	GPIO_InitTypeDef_t GPIO_LED_STRUCT = {0};

	RCC_GPIOA_CLK_ENABLE();
	GPIO_LED_STRUCT.pinNumber = GPIO_PIN_12;
	GPIO_LED_STRUCT.Mode = GPIO_MODE_OUTPUT;
	GPIO_LED_STRUCT.Speed = GPIO_OSPEEDR_LOW;
	GPIO_LED_STRUCT.Otype = GPIO_OTYPE_PP;
	GPIO_LED_STRUCT.PuPd = GPIO_PUPD_NOPULL;
	GPIO_Init(GPIOA, &GPIO_LED_STRUCT);

}
