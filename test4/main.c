

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
int32_t aaa = -1;
uint16_t bbb = 0x1234;

int16_t arr[4] = {
    1, 2, 3, 4
};

int main(void)
{
    p1.x = 0x12, p1.y = 0x3456;
    Point *p;

    p = &p1;
    p->x = 0xFF;

    int32_t ccc;
    ccc = aaa;

    int16_t bb;
    bb = arr[2];


    return 0;
}
