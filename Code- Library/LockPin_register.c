#include "stm32F446xx.h"

static void GPIO_LedConfig();
static void LockControl();

int main(void)
{
	GPIO_LedConfig();
	GPIO_LockPin(GPIOC, GPIO_PIN_13);
	LockControl();

	for(;;)
	{
		if (GPIO_Read_Pin(GPIOC,GPIO_PIN_13) == GPIO_PIN_RESET )
		{
			GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		}
		else
		{
			GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
		}
	}
}


static 	void GPIO_LedConfig()
{
	GPIO_InitTypeDef_t GPIO_Init_STRUCT = {0};
// CLCOK HATTININ AKTİVE EDİLMESİ
	RCC_GPIOA_CLK_ENABLE();
	RCC_GPIOC_CLK_ENABLE();

	GPIO_Init_STRUCT.pinNumber = GPIO_PIN_5;
	GPIO_Init_STRUCT.Mode = GPIO_MODE_OUTPUT;
	GPIO_Init_STRUCT.Speed = GPIO_OSPEEDR_LOW;
	GPIO_Init_STRUCT.Otype = GPIO_OTYPE_PP;
	GPIO_Init_STRUCT.PuPd = GPIO_PUPD_PULL_DOWN;
	GPIO_Init(GPIOA, &GPIO_Init_STRUCT);

	memset(&GPIO_Init_STRUCT, 0 , sizeof(GPIO_Init_STRUCT));		// YUKARIDAKİ STRUCT YAPISININ VERİLERİNİN TEMİZLENMESİ

	GPIO_Init_STRUCT.pinNumber = GPIO_PIN_13;
	GPIO_Init_STRUCT.Mode = GPIO_MODE_INPUT;
	GPIO_Init_STRUCT.PuPd = GPIO_PUPD_PULL_DOWN;

	GPIO_Init(GPIOC, &GPIO_Init_STRUCT);

}


static void LockControl()
{
	GPIO_InitTypeDef_t GPIO_Init_STRUCT = {0};
	GPIO_Init_STRUCT.pinNumber = GPIO_PIN_13;
	GPIO_Init_STRUCT.Mode = GPIO_MODE_OUTPUT;
	GPIO_Init_STRUCT.PuPd = GPIO_PUPD_NOPULL;

	GPIO_Init(GPIOC, &GPIO_Init_STRUCT);

}
