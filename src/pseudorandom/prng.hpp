#pragma once

#include <vector>
#include <cstdint>

using std::size_t;

namespace qcrypt::prng {


class PseudoRNG {
public:
    PseudoRNG();

    virtual uint8_t genByte() = 0;
    virtual uint32_t genWord();
    virtual uint64_t genDword();
    virtual uint8_t genBit();
    virtual std::vector<uint8_t> genBlock(size_t size_bytes);


    virtual ~PseudoRNG();
};

} // namespace qcrypt::prng
