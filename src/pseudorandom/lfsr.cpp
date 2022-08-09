#include <stdexcept>
#include <iostream>

#include "../util/bits.hpp"
#include "lfsr.hpp"


using namespace qcrypt;

using namespace qcrypt::prng;


LinearFSR32::~LinearFSR32() { }

LinearFSR32::LinearFSR32(uint32_t seed) {
    if (seed == 0) {
        std::cerr << "Warning: LFSR initialized with 0 seed!" << std::endl;
    }

    registers = seed;
}

uint8_t LinearFSR32::genBit() {
    doShift();

    return registers & 1;
}

uint8_t LinearFSR32::genByte() {
    uint8_t byte = 0;

    for (int i = 0; i < 8; i++) {
        doShift();
        byte |= (registers & 1);
        byte <<= 1;
    }

    return byte;
}

void LinearFSR32::doShift() {
    uint32_t tapped_bit = bit_parity(registers & taps);

    registers = (tapped_bit << 31) | (registers >> 1);
}


