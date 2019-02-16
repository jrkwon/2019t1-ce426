/*
 * sos.c
 *
 *  Created on: Feb 15, 2019
 *      Author: jkwon
 */
#include "gpiodriver.h"
#include "sos.h"

// uncomment the following line to use an external circuit
//#define USE_EXT_CIRCUIT

#ifdef USE_EXT_CIRCUIT
#define turn_on_led_and_delay       turn_on_ext_led_and_delay
#define turn_off_led_and_delay      turn_off_ext_led_and_delay
#define turn_on_led                 turn_on_ext_led
#define turn_off_led                turn_off_ext_led
#else
#define turn_on_led_and_delay       turn_on_onboard_led_and_delay
#define turn_off_led_and_delay      turn_off_onboard_led_and_delay
#define turn_on_led                 turn_on_onboard_led
#define turn_off_led                turn_off_onboard_led
#endif

//*****************************************************************************
//
// SOS (- - - --- --- --- - - -)
//
//*****************************************************************************

void sos_s_signal(void)
{
    turn_on_led_and_delay(SOS_LED, SOS_SHORT_DELAY);
    turn_off_led_and_delay(SOS_LED, SOS_SHORT_DELAY);
    turn_on_led_and_delay(SOS_LED, SOS_SHORT_DELAY);
    turn_off_led_and_delay(SOS_LED, SOS_SHORT_DELAY);
    turn_on_led_and_delay(SOS_LED, SOS_SHORT_DELAY);
    turn_off_led_and_delay(SOS_LED, SOS_SHORT_DELAY);
}

void sos_o_signal(void)
{
    turn_on_led_and_delay(SOS_LED, SOS_LONG_DELAY);
    turn_off_led_and_delay(SOS_LED, SOS_SHORT_DELAY);
    turn_on_led_and_delay(SOS_LED, SOS_LONG_DELAY);
    turn_off_led_and_delay(SOS_LED, SOS_SHORT_DELAY);
    turn_on_led_and_delay(SOS_LED, SOS_LONG_DELAY);
    turn_off_led_and_delay(SOS_LED, SOS_SHORT_DELAY);
}

void sos_on(void)
{
    sos_s_signal();
    sos_o_signal();
    sos_s_signal();
    systick_delay(SOS_LONG_DELAY);
}

void sos_off(void)
{
    turn_off_led(SOS_LED);
}
