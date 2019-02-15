

/**
 * main.c
 */

#define SYSCTL_RCGCGPIO_R       (*((volatile unsigned long *)0x400FE608))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
// this is for bit-specific access with array or pointer notations
#define GPIO_PORTF_DATA_BITS_R  ((volatile unsigned long *)0x40025000)

// these are for bit-specific access with indivisual addresses
//#define GPIO_PORTF_DATA_0_R       (*((volatile unsigned long *)0x40025004))
//#define GPIO_PORTF_DATA_1_R       (*((volatile unsigned long *)0x40025008))
//#define GPIO_PORTF_DATA_2_R       (*((volatile unsigned long *)0x40025010))
//#define GPIO_PORTF_DATA_3_R       (*((volatile unsigned long *)0x40025020))

#define RAM_BIT_BAND(offset, bit)    \
    (*((volatile unsigned long *)(0x22000000+0x20*(offset)+4*(bit))))

int main(void)
{
//    // simple bit-band testing.
//    //(*(unsigned long *)0x22000004) = 1; // only 1 or 0 possible.
//    RAM_BIT_BAND(0, 2) = 1; // bit-band test

    SYSCTL_RCGCGPIO_R = 0x20;
    GPIO_PORTF_AMSEL_R = 0;
    GPIO_PORTF_PCTL_R = 0;
    GPIO_PORTF_DIR_R = 0x0E;
    GPIO_PORTF_DEN_R = 0x1F;

//    GPIO_PORTF_DATA_R |= 0x02; // red
//    GPIO_PORTF_DATA_3_R = 0x08; // green
    GPIO_PORTF_DATA_BITS_R[2] = 2; // red
    *(GPIO_PORTF_DATA_BITS_R+4) = 4; // blue


    while(1)
        ;

	return 0;
}
