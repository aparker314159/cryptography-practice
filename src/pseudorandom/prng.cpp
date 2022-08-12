#include "prng.hpp"

using namespace qcrypt::prng;

PseudoRNG::PseudoRNG() {}

PseudoRNG::~PseudoRNG() {}

uint8_t PseudoRNG::genByte() {
    // By default, generate 8 bits and form them into a byte.
    uint8_t byte = 0;

    for (int i = 0; i < 8; i++) {
        byte |= genBit();
        byte <<= 1;
    }

    return byte;
}

uint32_t PseudoRNG::genWord() {

    // generate a byte 4 times, casting each to a 32 bit int
    uint32_t byte1 = genByte();
    uint32_t byte2 = genByte();
    uint32_t byte3 = genByte();
    uint32_t byte4 = genByte();

    return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}
uint64_t PseudoRNG::genDword() {

    // generate a word twice, casting each to 64 bits
    uint64_t word1 = genWord();
    uint64_t word2 = genWord();

    return (word1 << 32) | word2;
}

std::vector<uint8_t> PseudoRNG::genBlock(size_t size_bytes) {
    std::vector<uint8_t> bytes{};

    for (size_t i = 0; i < size_bytes; i++) {
        uint8_t byte = genByte();
        bytes.push_back(byte);
    }

    return bytes;
}


