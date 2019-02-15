

/**
## tried to change project name. it didn't go through github.

 * main.c
 */
#include <stdint.h>
#include <assert.h>

#define DEBUG

#define GPIO_PORTF_DATA_BITS_R  ((volatile unsigned long *)0x40025000)
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))

#define LED_RED 2
#define LED_BLUE 4
#define LED_GREEN 8

#define COUNT  900000

void delay(int count);

// make some sample variables here.

uint32_t u32variable = 0x12345678;
uint16_t u16variable = 0xABCD;

int main(void)
{
    uint32_t local_u32variable = 0x12345678;
    uint16_t local_u16variable = 0xABCD;

    // without this, you will see fault
    // *((unsigned int *)0x400FE608U) = 0x20U;
    *((unsigned int *)0x40025400U) = 0xEU;
    *((unsigned int *)0x4002551CU) = 0xEU;

    //assert(0); // test assert

    while(1) {
//        *((unsigned int *)0x400253FCU) = 0x2U;
        GPIO_PORTF_DATA_BITS_R[LED_RED] = LED_RED;
        delay(COUNT);
        GPIO_PORTF_DATA_R = LED_GREEN;
        delay(COUNT);
        GPIO_PORTF_DATA_R = 0;
        delay(COUNT);
    }


    return 0;
}
