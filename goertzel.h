#ifndef GOERTZEL_H
#define GOERTZEL_H

#include <stdint.h>

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t

#define s8 int8_t
#define s16 int16_t
#define s32 int32_t


u8 goertzel(const s8* pin_vect, const u16 pin_vect_len, const u16 freq_index);
u16 isqrt_newton(const u32 val);

#endif /* GOERTZEL_H */