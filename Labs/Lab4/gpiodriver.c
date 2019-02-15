/*
 * gpiodriver.c
 *
 *  Created on: Feb 14, 2019
 *      Author: jkwon
 */
#include "gpiodriver.h"

//*****************************************************************************
//
// GPIO registers (PORTF)
//
//*****************************************************************************

void init_gpio_portf(void)
{
    // make sure APB is used.
    SYSCTL_GPIOHBCTL_R &= ~SYSCTL_GPIOHBCTL_PORTF;
    SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_PORTF;
    // after clock gate for gpio port f is being set,
    // it's safe to wait a few clock cycle.
    asm (
        " nop\n"
        " nop\n"
    );

    /* ------
     * Writes to protected bits of the GPIO
     * Alternate Function Select (GPIOAFSEL) register (see page 668),
     * GPIO Pull Up Select (GPIOPUR) register (see page 674),
     * GPIO Pull-Down Select (GPIOPDR) register (see page 676),
     * and GPIO Digital Enable (GPIODEN) register (see page 679)
     * are not committed to storage
     * unless the GPIO Lock (GPIOLOCK) register (see page 681)
     * has been unlocked and the appropriate bits of
     * the GPIO Commit (GPIOCR) register (see page 682) have been set.
     */
    GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY; // without this switches are not working.
    GPIO_PORTF_CR_R |= (ONBOARD_SW1 | ONBOARD_SW2);

    GPIO_PORTF_AMSEL_R &= ~GPIO_PORTF_BITS;
    //GPIO_PORTF_PCTL_R &= 0xFFF0FFF0;

    GPIO_PORTF_DIR_R |= (ONBOARD_LED_RED|ONBOARD_LED_BLUE|ONBOARD_LED_GREEN);
    GPIO_PORTF_DIR_R &= ~(ONBOARD_SW1|ONBOARD_SW2);

    GPIO_PORTF_AFSEL_R &= ~GPIO_PORTF_BITS;
    GPIO_PORTF_DEN_R |= GPIO_PORTF_BITS;

    GPIO_PORTF_PUR_R |= (ONBOARD_SW1 | ONBOARD_SW2); // important!! without this, switches don't work.
}

bool read_onboard_sw1(void)
{
    return (GPIO_PF4 == 0) ? true : false;
}

bool read_onboard_sw2(void)
{
    return (GPIO_PF0 == 0) ? true : false;
}

void turn_on_onboard_led(int led)
{
    switch(led) {
    case ONBOARD_LED_RED:
        GPIO_PF1 |= ONBOARD_LED_RED;
        break;
    case ONBOARD_LED_BLUE:
        GPIO_PF2 |= ONBOARD_LED_BLUE;
        break;
    case ONBOARD_LED_GREEN:
        GPIO_PF3 |= ONBOARD_LED_GREEN;
        break;
    case ONBOARD_LED_ALL:
        GPIO_PF1 |= ONBOARD_LED_RED;
        GPIO_PF2 |= ONBOARD_LED_BLUE;
        GPIO_PF3 |= ONBOARD_LED_GREEN;
        break;
    }
}

void turn_off_onboard_led(int led)
{
    switch(led) {
    case ONBOARD_LED_RED:
        GPIO_PF1 &= ~ONBOARD_LED_RED;
        break;
    case ONBOARD_LED_BLUE:
        GPIO_PF2 &= ~ONBOARD_LED_BLUE;
        break;
    case ONBOARD_LED_GREEN:
        GPIO_PF3 &= ~ONBOARD_LED_GREEN;
        break;
    case ONBOARD_LED_ALL:
        GPIO_PF1 &= ~ONBOARD_LED_RED;
        GPIO_PF2 &= ~ONBOARD_LED_BLUE;
        GPIO_PF3 &= ~ONBOARD_LED_GREEN;
        break;
    }
}

//*****************************************************************************
//
// Interrupt
//
//*****************************************************************************

void disable_interrupt(void)
{
    //
    // Read PRIMASK and disable interrupts.
    //
    asm(" cpsid i\n");
}

void enable_interrupt(void)
{
    //
    // Read PRIMASK and enable interrupts.
    //
    asm(" cpsie i\n");
}

void init_gpio_portf_interrupt(void)
{
    GPIO_PORTF_IS_R &= ~(ONBOARD_SW1 | ONBOARD_SW2);
    GPIO_PORTF_IBE_R &= ~(ONBOARD_SW1 | ONBOARD_SW2);
    GPIO_PORTF_IEV_R &= ~(ONBOARD_SW1 | ONBOARD_SW2);
    GPIO_PORTF_ICR_R = (ONBOARD_SW1 | ONBOARD_SW2); // clear flag PF1 and PF4
    GPIO_PORTF_IM_R |= (ONBOARD_SW1 | ONBOARD_SW2); // arm interrupt on PF1 and PF4
    //NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000; // (g) priority 5
    NVIC_EN0_R = NVIC_EN0_PORTF;      // (h) enable interrupt 30 in NVIC

    enable_interrupt();
}


//*****************************************************************************
//
// GPIO PORTF Interrupt Handler
//
//*****************************************************************************
void gpio_portf_handler(void)
{
    if (GPIO_PORTF_RIS_R & ONBOARD_SW1) {
        turn_off_onboard_led(ONBOARD_LED_ALL);
        turn_on_onboard_led(ONBOARD_LED_RED);
    }
    else if (GPIO_PORTF_RIS_R & ONBOARD_SW2) {
        turn_off_onboard_led(ONBOARD_LED_ALL);
        turn_on_onboard_led(ONBOARD_LED_BLUE);
    }
    GPIO_PORTF_ICR_R = (ONBOARD_SW1 | ONBOARD_SW2); // clear flag PF1 and PF4
}

