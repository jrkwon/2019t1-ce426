/*
 * int_handlers.h
 *
 *  Created on: Feb 15, 2019
 *      Author: jkwon
 */

#ifndef INT_HANDLERS_H_
#define INT_HANDLERS_H_

extern bool onboard_sw1_pressed;
extern bool onboard_sw2_pressed;

void gpio_portf_handler(void);
void reset_sw_pressed(void);

#endif /* INT_HANDLERS_H_ */
