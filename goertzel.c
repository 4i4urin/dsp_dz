#include "goertzel.h"
#include "cos_table.h"
#include <stdio.h>


s16 get_cos(u16 index);


u8 goertzel(const s8* pin_vect, const u16 in_vect_len, const u16 freq_index)
{
    if (pin_vect == NULL)
        return 0;

    s32 u0 = 0;
    s32 u1 = 0;
    s32 u2 = 0;

    s32 cos_val = get_cos(freq_index);
    s32 sin_val = isqrt_newton( (1 << 24) - cos_val * cos_val );

    for (u16 i = 0; i < in_vect_len; i++)
    {
        u0 = ((cos_val * u1) >> 11) - u2 + pin_vect[i];
        u2 = u1;
        u1 = u0;
    }

    s32 res_re = (u0 << 12) - cos_val * u2;
    s32 res_im = -sin_val * u2;
    res_re >>= 12;
    res_im >>= 12;

    return 2 * isqrt_newton( (u32)(res_re*res_re) + (u32)(res_im*res_im)) / in_vect_len;
}


u8* goertzel_arr(
    const s8* pin_vect, const u16 in_vect_len, 
    const u16* freq_index, const u8 freq_index_len, u8* res)
{
    if (pin_vect == NULL || freq_index == NULL || res == NULL)
        return NULL;

    s32 u0 = 0;
    s32 u1 = 0;
    s32 u2 = 0;

    for (u8 findex = 0; findex < freq_index_len; findex++)
    {
        u0 = 0; u1 = 0; u2 = 0;
        
        s32 cos_val = get_cos(freq_index[findex]);
        s32 sin_val = isqrt_newton( (1 << 24) - cos_val * cos_val );

        for (u16 i = 0; i < in_vect_len; i++)
        {
            u0 = ((cos_val * u1) >> 11) - u2 + pin_vect[i];
            u2 = u1;
            u1 = u0;
        }

        s32 res_re = (u0 << 12) - cos_val * u2;
        s32 res_im = -sin_val * u2;
        res_re >>= 12;
        res_im >>= 12;

        res[findex] = 2 * isqrt_newton((u32)(res_re*res_re) + (u32)(res_im*res_im)) / in_vect_len;
    }
    return res;
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


s16 get_cos(u16 index)
{
    if (index <= 250)
        return table_cos[index];
    else if (index <= 500)
        return -table_cos[500 - index];
    else if (index <= 750)
        return -table_cos[index - 500];
    else if (index <= 1000)
        return table_cos[1000 - index];
    else
        return 0;
}

