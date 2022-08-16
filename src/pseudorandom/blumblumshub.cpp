#include <iostream>

#include "blumblumshub.hpp"

#include "../util/bits.hpp"


using namespace qcrypt::prng;


BlumBlumShub::BlumBlumShub(uint64_t seed):
    state{seed}
{
    std::cerr << "No safe primes given! Using (insecure) defaults instead." << std::endl;

    if (seed <= 1) {
        std::cerr << "Seed is 0 or 1 in BBS! Random numbers will not occur." << std::endl;
    }

    p = DEFAULT_P;
    q = DEFAULT_Q;

    p_times_q = p * q;
}

BlumBlumShub::BlumBlumShub(uint64_t seed, uint64_t p_, uint64_t q_):
    state{seed},
    p{p_},
    q{q_}
{
    if (seed <= 1) {
        std::cerr << "Seed is 0 or 1 in BBS! Random numbers will not occur." << std::endl;
    }

    p_times_q = p * q;
}


BlumBlumShub::~BlumBlumShub() {}


uint8_t BlumBlumShub::genBit() {
    state = (state * state) % p_times_q;
    return bit_parity(state);
}
