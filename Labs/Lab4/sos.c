/*
 * sos.c
 *
 *  Created on: Feb 15, 2019
 *      Author: jkwon
 */
#include "gpiodriver.h"
#include "sos.h"

//*****************************************************************************
//
// SOS (- - - --- --- --- - - -)
//
//*****************************************************************************

void sos_s_signal(void)
{
    turn_on_onboard_led_and_delay(SOS_LED, SOS_SHORT_DELAY);
    turn_off_onboard_led_and_delay(SOS_LED, SOS_SHORT_DELAY);
    turn_on_onboard_led_and_delay(SOS_LED, SOS_SHORT_DELAY);
    turn_off_onboard_led_and_delay(SOS_LED, SOS_SHORT_DELAY);
    turn_on_onboard_led_and_delay(SOS_LED, SOS_SHORT_DELAY);
    turn_off_onboard_led_and_delay(SOS_LED, SOS_SHORT_DELAY);
}

void sos_o_signal(void)
{
    turn_on_onboard_led_and_delay(SOS_LED, SOS_LONG_DELAY);
    turn_off_onboard_led_and_delay(SOS_LED, SOS_SHORT_DELAY);
    turn_on_onboard_led_and_delay(SOS_LED, SOS_LONG_DELAY);
    turn_off_onboard_led_and_delay(SOS_LED, SOS_SHORT_DELAY);
    turn_on_onboard_led_and_delay(SOS_LED, SOS_LONG_DELAY);
    turn_off_onboard_led_and_delay(SOS_LED, SOS_SHORT_DELAY);
}

void sos_signal(void)
{
    sos_s_signal();
    sos_o_signal();
    sos_s_signal();
    systick_delay(SOS_LONG_DELAY);
}
