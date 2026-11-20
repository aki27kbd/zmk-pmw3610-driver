#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "pmw3610_rotation.h"

int main(void) {
    struct pmw3610_rotation_state state;
    int32_t x = 100, y = 0;
    pmw3610_rotation_init(&state, -30);
    pmw3610_rotation_apply(&state, &x, &y);
    assert(x == 86 && y == -50); /* Both axes are produced in the first frame. */

    pmw3610_rotation_init(&state, 0);
    x = -137; y = 281;
    pmw3610_rotation_apply(&state, &x, &y);
    assert(x == -137 && y == 281);

    pmw3610_rotation_init(&state, -30);
    int32_t total_x = 0, total_y = 0;
    for (int i = 0; i < 10000; i++) {
        x = 1; y = 0;
        pmw3610_rotation_apply(&state, &x, &y);
        total_x += x; total_y += y;
    }
    assert(fabs(total_x - 8660.254037844386) < 1.01);
    assert(fabs(total_y + 5000.0) < 1.01);

    pmw3610_rotation_init(&state, -30);
    total_x = 0; total_y = 0;
    for (int i = 0; i < 10000; i++) {
        x = 0; y = 1;
        pmw3610_rotation_apply(&state, &x, &y);
        total_x += x; total_y += y;
    }
    assert(fabs(total_x - 5000.0) < 1.01);
    assert(fabs(total_y - 8660.254037844386) < 1.01);

    pmw3610_rotation_init(&state, -30);
    total_x = 0; total_y = 0;
    for (int i = 0; i < 10000; i++) {
        x = i % 2 ? -1 : 1; y = i % 2 ? -3 : 3;
        pmw3610_rotation_apply(&state, &x, &y);
        total_x += x; total_y += y;
    }
    assert(total_x == 0 && total_y == 0);
    puts("PASS: complete first frame, zero rotation, fractional X/Y movement, and reversals");
    return 0;
}
