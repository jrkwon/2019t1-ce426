/*
 * gpiodriver.c
 *
 *  Created on: Feb 14, 2019
 *      Author: jkwon
 */
#include "gpiodriver.h"

//*****************************************************************************
//
// The prototypes of local functions
//
//*****************************************************************************
static uint32_t get_tick_ctl(void);

//*****************************************************************************
//
// local variables
//
//*****************************************************************************
static volatile uint32_t g_tick_ctl;
// to stop systick_wait immediately.
// systick_delay() will have a proper delay only if this value is false.
static bool immediate_stop = false;

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

void turn_on_onboard_led(ONBOARD_LED led)
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

void turn_off_onboard_led(ONBOARD_LED led)
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

void turn_on_onboard_led_and_delay(ONBOARD_LED led, uint32_t delay)
{
    turn_on_onboard_led(led);
    systick_delay(delay);
}

void turn_off_onboard_led_and_delay(ONBOARD_LED led, uint32_t delay)
{
    turn_off_onboard_led(led);
    systick_delay(delay);
}

//*****************************************************************************
//
// GPIO registers (PORTA)
//
//*****************************************************************************

void init_gpio_porta(void)
{
    // TODO:
}

bool read_ext_sw1(void)
{
    // TODO:
    return false;
}

bool read_ext_sw2(void)
{
    // TODO:
    return false;
}

void turn_on_ext_led(EXT_LED led)
{
    // TODO:
}

void turn_off_ext_led(EXT_LED led)
{
    // TODO:
}

void turn_on_ext_led_and_delay(EXT_LED led, uint32_t delay)
{
    turn_on_ext_led(led);
    systick_delay(delay);
}

void turn_off_ext_led_and_delay(EXT_LED led, uint32_t delay)
{
    turn_off_ext_led(led);
    systick_delay(delay);
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

void init_systick(void)
{
    NVIC_ST_CTRL_R  = (1U << 2) | (1U << 1) | 1U;
    NVIC_ST_RELOAD_R = SYS_CLOCK_HZ/1000 - 1;   // roughly 1ms
    NVIC_ST_CURRENT_R = 0;
}

static uint32_t get_tick_ctl(void)
{
    uint32_t tick_ctl;
    __asm("    cpsid    i\n"); // disable irq
    tick_ctl = g_tick_ctl;
    __asm("    cpsie    i\n"); // enable irq
    return tick_ctl;
}

void systick_disable_delay(void)
{
    immediate_stop = true;
}

// systick is enabled by default after systick_init
void systick_enable_delay(void)
{
    immediate_stop = false;
}

void systick_delay(uint32_t ms)
{
    uint32_t start = get_tick_ctl();
    while(((get_tick_ctl() - start) < ms) && !immediate_stop)
        ;
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

void init_gpio_porta_interrupt(void)
{
    // TODO:
}

//*****************************************************************************
// systick_handler stays inside gpiodriver.c since there is no need
// to be changed by the user.
// All other interrupt handlers will be int_handers.c
void systick_handler(void)
{
    g_tick_ctl++;
}

