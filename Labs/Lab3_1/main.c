#define SYSCTL_GPIOHBCTL_R          (*(volatile unsigned int *)0x400FE06C)
#define GPIOHBCTL_PORTF             0x20

#define SYSCTL_RCGCGPIO_R           (*(volatile unsigned int *)0x400FE608)
#define RCGCGPIO_PORTF              0x20

#define GPIO_UNLOCK_VALUE           0x4C4F434B

#define GPIO_PORTF_DATA_BITS_R      ((volatile unsigned int *)0x40025000)
#define GPIO_PORTF_DATA_R           (*(volatile unsigned int *)0x400253FC)
#define GPIO_PORTF_DIR_R            (*(volatile unsigned int *)0x40025400)
#define GPIO_PORTF_AFSEL_R          (*(volatile unsigned int *)0x40025420)
#define GPIO_PORTF_DEN_R            (*(volatile unsigned int *)0x4002551C)
#define GPIO_PORTF_AMSEL_R          (*(volatile unsigned int *)0x40025528)
#define GPIO_PORTF_PUR_R            (*(volatile unsigned int *)0x40025510)
#define GPIO_PORTF_LOCK_R           (*(volatile unsigned int *)0x40025520)
#define GPIO_PORTF_CR_R             (*(volatile unsigned int *)0x40025524)
#define GPIO_PORTF_PCTL_R           (*(volatile unsigned int *)0x4002552C)

#define GPIO_PF0                    (*(volatile unsigned int *)0x40025004)
#define GPIO_PF1                    (*(volatile unsigned int *)0x40025008)
#define GPIO_PF2                    (*(volatile unsigned int *)0x40025010)
#define GPIO_PF3                    (*(volatile unsigned int *)0x40025020)
#define GPIO_PF4                    (*(volatile unsigned int *)0x40025040)

#define LED_RED     0x02
#define LED_BLUE    0x04
#define LED_GREEN   0x08

#define SW1         0x01
#define SW2         0x10

/**
 * main.c
 */
int main(void)
{
    // init GPIO F
    SYSCTL_RCGCGPIO_R = 0x20;

    // following a few lines are added here for switch interface
    GPIO_PORTF_LOCK_R = GPIO_UNLOCK_VALUE; // without this switches are not working.
    GPIO_PORTF_CR_R |= (SW1 | SW2);
    GPIO_PORTF_PUR_R |= (SW1 | SW2);

    GPIO_PORTF_AMSEL_R = 0;
    GPIO_PORTF_PCTL_R = 0;
    GPIO_PORTF_DIR_R = 0x0E;
    GPIO_PORTF_DEN_R = 0x1F;

    while (1)
       ;

	return 0;
}
