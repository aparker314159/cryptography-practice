#pragma once

#include <cstdint>


#define GET_BIT(x,n)     ( ((x) & (1U << (n))) >> n )
#define CHECK_BIT(x,n)   ( ((x) & (1U << (n))) >> n )

#define SET_BIT(x,n)     ( (x) |=  (1U << (n)) )
#define CLEAR_BIT(x,n)   ( (x) &= ~(1U << (n)) )
#define TOGGLE_BIT(x,n)  ( (x) ^=  (1U << (n)) )


// Returns 1 for odd parity, 0 for even
inline uint32_t bit_parity(uint32_t n) {
    uint32_t y;

    y = n ^ (n>>1);

    y = y ^ (y >> 2);
    y = y ^ (y >> 4);
    y = y ^ (y >> 8);
    y = y ^ (y >> 16);

    return y & 1U;
}
