#include <iostream>
#include <random>

#include "../src/pseudorandom/lfsr.hpp"
#include "../src/pseudorandom/blumblumshub.hpp"
#include "../src/util/bits.hpp"

#include "../src/stream/trivium.hpp"

using namespace qcrypt;

int main() {

    std::random_device r;
    std::uniform_int_distribution<uint32_t> dist(1, ~0U);

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

    auto trivium_key = stream::Trivium::genKey();

    std::cout << std::endl << trivium_key.to_string() << std::endl;

    stream::Trivium triv{trivium_key};

    std::vector<uint8_t> message{'H','e','l','l','o',' ','w','o','r','l','d'};

    auto triv_ciphertext = triv.encrypt(message);
    for (const auto& b : triv_ciphertext) {
        std::cout << std::hex << +b << ' ';
    }
    std::cout << std::endl;

    auto triv_plaintext = triv.decrypt(triv_ciphertext);
    for (const auto& b : triv_plaintext) {
        std::cout << b << std::endl;
    }
}



