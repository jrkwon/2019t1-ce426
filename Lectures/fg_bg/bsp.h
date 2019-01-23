/*
 * bsp.h
 *
 *  Created on: Jan 3, 2019
 *      Author: jkwon
 */

#ifndef BSP_H_
#define BSP_H_

#include "tm4c123gh6pm.h"

#define LED_RED     2   // 1U << 1
#define LED_BLUE    4   // 1U << 2
#define LED_GREEN   8   // 1U << 3

void enable_portf(void);
void init_systick(void);
void disable_interrupt(void);
void enable_interrupt(void);

#endif /* BSP_H_ */
