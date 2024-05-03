#include "goertzel.h"
#include <math.h>
#include <stdio.h>

#define PI 3.141592653589793


u8 goertzel(const s8* pin_vect, const u16 pin_vect_len, const u16 freq_index)
{
    s32 u0 = 0;
    s32 u1 = 0;
    s32 u2 = 0;

    s32 cos_val = cos(2*PI*freq_index/pin_vect_len) * 2 * 10000;
    for (u16 i = 0; i < pin_vect_len; i++)
    {
        u0 = cos_val * u1 / 10000 - u2 + pin_vect[i];
        u2 = u1;
        u1 = u0;
    }

    s32 res_re = u0 * 10000 - cos(2*PI*freq_index/pin_vect_len) * 10000 * u2;
    s32 res_im = -sin(2*PI*freq_index/pin_vect_len) * 10000 * u2;
    res_re /= 10000;
    res_im /= 10000;
    printf("res_re = %d res_im = %d\n", res_re, res_im);

    return 2 * isqrt_newton( (s32)(res_re*res_re) + (s32)(res_im*res_im)) / pin_vect_len;
}


// Square root of integer
u16 isqrt_newton(const u32 val)
{
    // Zero yields zero
    // One yields one
    if (val <= 1)
        return 0;

    // Initial estimate (must be too high)
    register u32 x0 = val >> 1;

    // Update
    register u32 x1 = (x0 + val / x0) >> 1;

    while (x1 < x0) // Bound check
    {
        x0 = x1;
        x1 = (x0 + val / x0) >> 1;
    }
    // was return (u16) x0;
    return (u16) (x0 <= 1) ? 0 : x0;
}

