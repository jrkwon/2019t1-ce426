/*
 * int_handlers.c
 *
 *  Created on: Feb 15, 2019
 *      Author: jkwon
 */

#include "gpiodriver.h"
#include "int_handlers.h"

bool onboard_sw1_pressed = false;
bool onboard_sw2_pressed = false;
bool ext_sw1_pressed = false;
bool ext_sw2_pressed = false;

void gpio_portf_handler(void)
{
    if (GPIO_PORTF_RIS_R & ONBOARD_SW1) {
        onboard_sw1_pressed = true;
        systick_enable_delay();
    }
    else if (GPIO_PORTF_RIS_R & ONBOARD_SW2) {
        onboard_sw2_pressed = true;
        systick_disable_delay();
    }
    GPIO_PORTF_ICR_R = (ONBOARD_SW1 | ONBOARD_SW2); // clear flag PF1 and PF4
}

void gpio_porta_handler(void)
{
    // TODO:
    // you must use ext_sw1_pressed and ext_sw2_pressed to indicate
    // a switch press state.
}


