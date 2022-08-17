#include "trivium.hpp"

#include <iostream>

#define IV_SIZE_BYTES 10


using namespace qcrypt::stream;


Trivium::Trivium(KeyType k):
    key{k},
    iv_counter{0}
{

}


Trivium::~Trivium() {}

Trivium::KeyType Trivium::genKey() {
    std::random_device rd{};
    // Chooses true or false with equal probability
    std::bernoulli_distribution dist{0.5};

    std::bitset<80> bits;

    for (int i = 0; i < 80; i++) {
        bits[i] = dist(rd);
    }

    return bits;
}

std::bitset<80> Trivium::genIV() {
    std::random_device rd{};

    std::uniform_int_distribution<uint16_t> dist{0, 65535};

    std::bitset<80> iv;
    iv.reset();

    iv |= dist(rd);
    iv <<= 64;

    iv |= iv_counter++;

    return iv;
}

std::vector<uint8_t> Trivium::genStream(size_t byte_count) {
    std::vector<uint8_t> stream;

    stream.resize(byte_count);

    for (size_t i = 0; i < byte_count; i++) {
        uint8_t byte = 0;
        for (int j = 0; j < 8; j++) {
            byte |= computeBit();
            byte <<= 1;
        }

        stream[i] = byte;
    }


    return stream;
}

void Trivium::initialize(std::bitset<80> iv) {

    ra.reset();
    rb.reset();
    rc.reset();

    for (int i = 0; i < 80; i++) {
        ra[i] = key[i];
        rb[i] = iv[i];
    }

    rc[110] = 1;
    rc[109] = 1;
    rc[108] = 1;

    for (int i = 0; i < 4*288; i++) {
        computeBit();
    }
}

uint8_t Trivium::computeBit() {
    // Recall that true is 1, false is 0
    // != acts as XOR
    bool t1 = (ra[65] != ra[92]);
    bool t2 = (rb[68] != rb[83]);
    bool t3 = (rc[65] != rc[110]);

    uint8_t bit = (t1 != t2) != t3 ? 1 : 0;

    t1 = (t1 != (ra[90]  && ra[91] )) != rb[77];
    t2 = (t2 != (rb[81]  && rb[82] )) != rb[86];
    t3 = (t3 != (rc[108] && rc[109])) != ra[68];

    ra <<= 1; ra[0] = t1;
    rb <<= 1; rb[0] = t2;
    rc <<= 1; rc[0] = t3;

    return bit;
}

std::vector<uint8_t> Trivium::encrypt(const std::vector<uint8_t>& plaintext) {

    std::vector<uint8_t> ciphertext;
    auto iv = genIV();

    initialize(iv);

    /* Write the IV as 10 bytes. */

    auto iv_copy = iv;

    const auto mask = std::bitset<80>{0xFF};
    for (int i = 0; i < IV_SIZE_BYTES; i++) {
        uint8_t byte = ((uint8_t) (iv_copy & mask).to_ulong());
        ciphertext.push_back(byte);
        iv_copy >>= 8;
    }

    std::cout << "IV: " << iv << std::endl;


    /* Write the message XOR'ed with the stream. */

    auto stream = genStream(plaintext.size());


    for (size_t i = 0; i < plaintext.size(); i++) {
        ciphertext.emplace_back(plaintext[i] ^ stream[i]);
    }

    return ciphertext;
}


std::vector<uint8_t> Trivium::decrypt(const std::vector<uint8_t>& ciphertext) {

    std::vector<uint8_t> plaintext;

    std::bitset<80> iv;
    iv.reset();

    /* Read the IV */
    for (int i = IV_SIZE_BYTES - 1; i >= 0; i--) {
        iv <<= 8;
        iv |= ciphertext[i];
    }

    initialize(iv);

    auto stream = genStream(ciphertext.size() - IV_SIZE_BYTES);

    for (size_t i = 0; i < ciphertext.size() - IV_SIZE_BYTES; i++) {
        plaintext.emplace_back(ciphertext[i + IV_SIZE_BYTES] ^ stream[i]);
    }


    return plaintext;
}
