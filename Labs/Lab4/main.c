#include "gpiodriver.h"
#include "sos.h"

void super_loop(void)
{
    bool start_sos = false;

    for(;;) {
        if(onboard_sw1_pressed)
            start_sos = true;
        if(onboard_sw2_pressed)
            start_sos = false;

        if(start_sos)
            sos_signal();

    }
}

int main(void)
{
    init_systick();
    init_gpio_portf();
    init_gpio_portf_interrupt();

    super_loop();
    return 0;
}
