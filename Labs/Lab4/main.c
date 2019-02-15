#include "gpiodriver.h"

void super_loop(void)
{
    for(;;)
        ;
}

void test_cases(void)
{

}

int main(void)
{
    init_gpio_portf();
    init_gpio_portf_interrupt();

    test_cases();

    super_loop();
    return 0;
}
