#include <stdio.h>
#include <stdint.h>

#define GPIO_PIN_0 		(uint16_t)(0x0001)	// 0000 0000 0000 0001					GPIO PIN 0 SELECTED
#define GPIO_PIN_1 		(uint16_t)(0x0002)	// 0000 0000 0000 0010					GPIO PIN 1 SELECTED
#define GPIO_PIN_2 		(uint16_t)(0x0004)  // 0000 0000 0000 0100					GPIO PIN 2 SELECTED
#define GPIO_PIN_3 		(uint16_t)(0x0008)  // 0000 0000 0000 1000					GPIO PIN 3 SELECTED
#define GPIO_PIN_4 		(uint16_t)(0x0010)  // 0000 0000 0001 0000					GPIO PIN 4 SELECTED
#define GPIO_PIN_5 		(uint16_t)(0x0020)  // 0000 0000 0010 0000					GPIO PIN 5 SELECTED
#define GPIO_PIN_6 		(uint16_t)(0x0040)  // 0000 0000 0100 0000					GPIO PIN 6 SELECTED
#define GPIO_PIN_7 		(uint16_t)(0x0080)  // 0000 0000 1000 0000					GPIO PIN 7 SELECTED
#define GPIO_PIN_8 		(uint16_t)(0x0100)  // 0000 0001 0000 0000					GPIO PIN 8 SELECTED
#define GPIO_PIN_9 		(uint16_t)(0x0200)  // 0000 0010 0000 0000					GPIO PIN 9 SELECTED
#define GPIO_PIN_10		(uint16_t)(0x0400)  // 0000 0100 0000 0000					GPIO PIN 10 SELECTED
#define GPIO_PIN_11 	(uint16_t)(0x0800)	// 0000 1000 0000 0000					GPIO PIN 11 SELECTED
#define GPIO_PIN_12		(uint16_t)(0x1000)	// 0001 0000 0000 0000					GPIO PIN 12 SELECTED
#define GPIO_PIN_13		(uint16_t)(0x2000)	// 0010 0000 0000 0000					GPIO PIN 13 SELECTED
#define GPIO_PIN_14 	(uint16_t)(0x4000)	// 0100 0000 0000 0000					GPIO PIN 14 SELECTED
#define GPIO_PIN_15		(uint16_t)(0x8000)	// 1000 0000 0000 0000					GPIO PIN 15 SELECTED
#define GPIO_PIN_ALL 	(uint16_t)(0xFFFF)	// 0000 0000 0000 0000					GPIO PIN ALL SELECTED

#define Max_gpio_pin_number     (uint16_t)(16U)

int main(void)
{

    uint16_t GPIO_Pin_config = GPIO_PIN_10 | GPIO_PIN_2 |GPIO_PIN_7 | GPIO_PIN_8; 
    for(uint16_t position = 0 ; position < Max_gpio_pin_number ; position++)
    {
        uint16_t fake_position = (0x1 << position);
        uint16_t isThere = (GPIO_Pin_config)& fake_position;
            if (isThere == fake_position)
            {
                printf("%d is your position : pin value  %#X is your fake value , %#X is there your real Value \n",position,fake_position,isThere);
            }
    }


    return 0;
}