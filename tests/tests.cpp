#include <iostream>
#include <random>

#include "../src/pseudorandom/lfsr.hpp"
#include "../src/pseudorandom/blumblumshub.hpp"
#include "../src/util/bits.hpp"

using namespace qcrypt;

int main() {

    std::random_device r;
    std::uniform_int_distribution<uint32_t> dist(1, ~0);

    prng::LinearFSR32 lfsr{dist(r)};

    for (int i = 0; i < 20; i++) {
        uint32_t word = lfsr.genWord();
        std::cout << std::hex << word << ' ';
    }

    std::cout << std::endl;

    prng::BlumBlumShub bbs{dist(r)};
    for (int i = 0; i < 20; i++) {
        uint32_t word = bbs.genWord();
        std::cout << std::hex << word << ' ';
    }
}


