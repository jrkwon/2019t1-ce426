#include "gpiodriver.h"
#include "sos.h"

// state management using finite state machine
typedef enum {
    SOS_SHOW,
    SOS_STOP
} SOS_STATE;

void super_loop(void)
{
    SOS_STATE state = SOS_STOP;

    for(;;) {
        switch(state) {
        case SOS_SHOW:
            sos_signal();
            if(onboard_sw2_pressed) {
                state = SOS_STOP;
                onboard_sw2_pressed = false;
            }
            break;
        case SOS_STOP:
            if(onboard_sw1_pressed) {
                state = SOS_SHOW;
                onboard_sw1_pressed = false;
            }
            break;
        }
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
