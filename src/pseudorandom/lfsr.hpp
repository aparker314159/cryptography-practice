#pragma once

#include "prng.hpp"

namespace qcrypt {

namespace prng {

/*
 * Implements a linear feedback shift register with 32 bits.
 * Taps are on bits 1,5,6,31 (zero-indexed), which should give the maximum period
 * according to https://www.eetimes.com/tutorial-linear-feedback-shift-registers-lfsrs-part-1/
 */
class LinearFSR32 : public PseudoRNG {
public:
    uint8_t genByte();
    uint8_t genBit();

    LinearFSR32(uint32_t seed);

    ~LinearFSR32();

private:
    uint32_t registers;

    // Set taps based on http://users.ece.cmu.edu/~koopman/lfsr/
    constexpr static uint32_t taps = 0x8000019F;

    // does a shift of the LFSR, and appends the new bit of the register to the least significant bit in the register variable.
    void doShift();
};


} // namespace prng


} // namespace qcrypt
