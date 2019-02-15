

/**
 * main.c
 */

#include <stdint.h>

uint8_t     u8a, u8 = 0xabU;
uint16_t    u16a, u16 = 0x1234U;
uint32_t    u32a, u32 = 0x12345678U;
int16_t     s16;
int8_t      s8;

int main(void)
{
    u8a = u8;
    u16a = u16;
    u32a = u32;

    u16 = 100;
    s8 = 10 - u16;
    return 0;
}
