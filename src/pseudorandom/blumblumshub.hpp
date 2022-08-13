#pragma once

#include "prng.hpp"

namespace qcrypt::prng {

class BlumBlumShub : public PseudoRNG {
public:
    BlumBlumShub(uint64_t seed);
    BlumBlumShub(uint64_t seed, uint64_t p, uint64_t q);

    uint8_t genBit();

    ~BlumBlumShub();

private:
    uint64_t state;
    uint64_t p, q;
    uint64_t p_times_q;

    // THESE DEFAULTS ARE TOO SMALL FOR CRYPTOGRAPHIC USE.
    constexpr static uint64_t DEFAULT_P = 2359103;
    constexpr static uint64_t DEFAULT_Q = 2474183;

};

} // namespace qcrypt::prng
