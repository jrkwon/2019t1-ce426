#include "gpiodriver.h"
#include "sos.h"

// uncomment the following line to use an external circuit
//#define USE_EXT_CIRCUIT

#ifdef USE_EXT_CIRCUIT
#define sw1_pressed     ext_sw1_pressed
#define sw2_pressed     ext_sw2_pressed
#else
#define sw1_pressed     onboard_sw1_pressed
#define sw2_pressed     onboard_sw2_pressed
#endif

// state management using finite state machine
typedef enum {
    SOS_ON,
    SOS_OFF
} SOS_STATE;

void super_loop(void)
{
    SOS_STATE state = SOS_OFF;

    for(;;) {
        switch(state) {
        case SOS_ON:
            sos_on();
            if(sw2_pressed) {
                state = SOS_OFF;
                sw2_pressed = false;
            }
            break;
        case SOS_OFF:
            sos_off();
            if(sw1_pressed) {
                state = SOS_ON;
                sw1_pressed = false;
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
