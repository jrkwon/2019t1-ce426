/*
 * gpiodriver.h
 *
 *  Created on: Feb 14, 2019
 *      Author: jkwon
 */

#ifndef GPIODRIVER_H_
#define GPIODRIVER_H_

#include "tm4c123gh6pm.h"
#include <stdbool.h>
#include <stdint.h>

//*****************************************************************************
//
// RGCGGPIO bits for GPIO PORTF and PORTA
//
//*****************************************************************************
#define SYSCTL_RCGCGPIO_PORTF       SYSCTL_RCGCGPIO_R5
#define SYSCTL_RCGCGPIO_PORTA       SYSCTL_RCGCGPIO_R0

//*****************************************************************************
//
// GPIO registers (PORTF)
//
//*****************************************************************************
#define GPIO_PORTF_BASE     0x40025000
#define GPIO_PF0            (*(volatile uint32_t *)(GPIO_PORTF_BASE + (1U<<2)))
#define GPIO_PF1            (*(volatile uint32_t *)(GPIO_PORTF_BASE + (1U<<3)))
#define GPIO_PF2            (*(volatile uint32_t *)(GPIO_PORTF_BASE + (1U<<4)))
#define GPIO_PF3            (*(volatile uint32_t *)(GPIO_PORTF_BASE + (1U<<5)))
#define GPIO_PF4            (*(volatile uint32_t *)(GPIO_PORTF_BASE + (1U<<6)))

#define GPIO_PORTF_BITS     0x1F    // lower 5 bits

//*****************************************************************************
//
// On board LEDs and switches
//
//*****************************************************************************
#define ONBOARD_LED_RED     0x02
#define ONBOARD_LED_BLUE    0x04
#define ONBOARD_LED_GREEN   0x08
#define ONBOARD_LED_ALL     0x0E

#define ONBOARD_SW1         0x10
#define ONBOARD_SW2         0x01

//*****************************************************************************
//
// GPIO registers (PORTA)
//
//*****************************************************************************
#define GPIO_PORTA_BASE     0x40004000
#define GPIO_PA0            (*(volatile uint32_t *)(GPIO_PORTA_BASE + (1U<<2)))
#define GPIO_PA1            (*(volatile uint32_t *)(GPIO_PORTA_BASE + (1U<<3)))
#define GPIO_PA2            (*(volatile uint32_t *)(GPIO_PORTA_BASE + (1U<<4)))
#define GPIO_PA3            (*(volatile uint32_t *)(GPIO_PORTA_BASE + (1U<<5)))
#define GPIO_PA4            (*(volatile uint32_t *)(GPIO_PORTA_BASE + (1U<<6)))
#define GPIO_PA5            (*(volatile uint32_t *)(GPIO_PORTA_BASE + (1U<<7)))
#define GPIO_PA6            (*(volatile uint32_t *)(GPIO_PORTA_BASE + (1U<<8)))
#define GPIO_PA7            (*(volatile uint32_t *)(GPIO_PORTA_BASE + (1U<<9)))

#define GPIO_PORTA_BITS     0xFF    // 8 bits


//*****************************************************************************
//
// Interrupt related
//
//*****************************************************************************

// NVIC interrupt enable register
#define NVIC_EN0_PORTA      0x00000001;      // bit 30 in NVIC_EN0
#define NVIC_EN0_PORTF      0x40000000;      // bit 30 in NVIC_EN0

//*****************************************************************************
//
// Function prototypes
//
//*****************************************************************************
void init_gpio_portf(void);
bool read_onboard_sw1(void);
bool read_onboard_sw2(void);
void turn_on_onboard_led(int led);
void turn_off_onboard_led(int led);

void init_gpio_portf_interrupt(void);

#endif /* GPIODRIVER_H_ */
