

/**
 * main.c
 */

#include <stdint.h>

typedef struct {
    uint8_t x;
    uint16_t y;
} Point;

//Point p1 = { 0x12, 0x3456};
Point p1;

int main(void)
{
    p1.x = 0x12, p1.y = 0x3456;
    Point *p;

    p = &p1;
    p->x = 0xFF;

    return 0;
}
