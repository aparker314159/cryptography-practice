#pragma once

#include <bitset>
#include <random>
#include <cstdint>


namespace qcrypt::stream {

class Trivium {

public:

    typedef std::bitset<80> KeyType;

    Trivium(KeyType key_);
    ~Trivium();

    static KeyType genKey();

    std::vector<uint8_t> encrypt(const std::vector<uint8_t>& plaintext);
    std::vector<uint8_t> decrypt(const std::vector<uint8_t>& ciphertext);


private:
    KeyType key;

    std::vector<uint8_t> genStream(size_t byte_count);

    std::bitset<93> ra;
    std::bitset<84> rb;
    std::bitset<111> rc;



    /*
     * Generates an initial vector, consisting of 16 bits of randomness and a 64 bit counter.
     */
    uint64_t iv_counter;
    std::bitset<80> genIV();


    void initialize(std::bitset<80> iv);

    uint8_t computeBit();
};




} // namespace qcrypt::stream
