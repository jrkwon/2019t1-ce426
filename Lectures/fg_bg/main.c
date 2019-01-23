

/**

 * main.c
 */
#include <stdint.h>
#include <assert.h>

#include "bsp.h"
#include "delay.h"

typedef enum {
    INIT,
    ON,
    OFF
} LED_STATE_E;

LED_STATE_E state = INIT;

int main(void)
{
    uint32_t start;

    enable_portf();
    init_systick();

    enable_interrupt();

    // status machine version
    while(1) {
        switch(state) {
        case INIT:
            start = get_tick_ctl();
            state = ON;
            break;
        case ON:
            if((get_tick_ctl() - start) > 500) {
                GPIO_PORTF_DATA_BITS_R[LED_BLUE] |= LED_BLUE;
                start = get_tick_ctl();
                state = OFF;
            }
            break;
        case OFF:
            if((get_tick_ctl() - start) > 500) {
                GPIO_PORTF_DATA_BITS_R[LED_BLUE] &= ~LED_BLUE;
                start = get_tick_ctl();
                state = ON;
            }
            break;
        }
    }

#if 0 // sequential version
    while(1) {
        // could have race conditions
        GPIO_PORTF_DATA_BITS_R[LED_BLUE] |= LED_BLUE;
        sys_delay(500);
        GPIO_PORTF_DATA_BITS_R[LED_BLUE] &= ~LED_BLUE;
        sys_delay(500);
    }
#endif

    return 0;
}
