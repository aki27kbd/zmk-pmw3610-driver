#pragma once

#include <math.h>
#include <stdint.h>

struct pmw3610_rotation_state {
    float cosine;
    float sine;
    float remainder_x;
    float remainder_y;
};

static inline void pmw3610_rotation_init(struct pmw3610_rotation_state *state, int degrees) {
    const float radians = degrees * (3.14159265358979323846f / 180.0f);
    *state = (struct pmw3610_rotation_state){.cosine = cosf(radians), .sine = sinf(radians)};
}

static inline void pmw3610_rotation_apply(struct pmw3610_rotation_state *state,
                                         int32_t *x, int32_t *y) {
    const float rotated_x = *x * state->cosine - *y * state->sine + state->remainder_x;
    const float rotated_y = *x * state->sine + *y * state->cosine + state->remainder_y;
    *x = (int32_t)rotated_x;
    *y = (int32_t)rotated_y;
    state->remainder_x = rotated_x - *x;
    state->remainder_y = rotated_y - *y;
}
