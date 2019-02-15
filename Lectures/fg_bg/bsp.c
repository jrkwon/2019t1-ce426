/*
 * bsp.c
 *
 *  Created on: Jan 3, 2019
 *      Author: jkwon
 */
#include "bsp.h"

#define SYS_CLOCK_HZ    16000000U

void enable_portf(void)
{
    SYSCTL_RCGCGPIO_R = 0x20U;
    GPIO_PORTF_DIR_R = 0xEU;
    GPIO_PORTF_DEN_R = 0xEU;
}

void disable_interrupt(void) {
    //
    // Read PRIMASK and disable interrupts.
    //
    __asm("    cpsid    i\n");
}

void enable_interrupt(void) {
    //
    // Read PRIMASK and enable interrupts.
    //
    __asm("    cpsie   i\n");
}

void init_systick(void)
{
    NVIC_ST_CTRL_R  = (1U << 2) | (1U << 1) | 1U;
    NVIC_ST_RELOAD_R = SYS_CLOCK_HZ/1000 - 1;
    NVIC_ST_CURRENT_R = 0;
}



