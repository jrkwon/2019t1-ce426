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

void gpio_portf_handler(void)
{
    if (GPIO_PORTF_RIS_R & ONBOARD_SW1) {
        onboard_sw1_pressed = true;
        onboard_sw2_pressed = false;
        g_immediate_stop = false;
    }
    else if (GPIO_PORTF_RIS_R & ONBOARD_SW2) {
        onboard_sw1_pressed = false;
        onboard_sw2_pressed = true;
        g_immediate_stop = true;
    }
    GPIO_PORTF_ICR_R = (ONBOARD_SW1 | ONBOARD_SW2); // clear flag PF1 and PF4
}

void reset_sw_pressed(void)
{
    onboard_sw1_pressed = false;
    onboard_sw2_pressed = false;
}

