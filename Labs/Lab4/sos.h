/*
 * sos.h
 *
 *  Created on: Feb 15, 2019
 *      Author: jkwon
 */

#ifndef SOS_H_
#define SOS_H_

/*
 * sos.c
 *
 *  Created on: Feb 15, 2019
 *      Author: jkwon
 */
#include "gpiodriver.h"

#define SOS_SHORT_DELAY     200
#define SOS_LONG_DELAY      (SOS_SHORT_DELAY*4)

#define SOS_LED             ONBOARD_LED_RED

void sos_s_signal(void);
void sos_o_signal(void);
void sos_on(void);
void sos_off(void);

#endif /* SOS_H_ */
