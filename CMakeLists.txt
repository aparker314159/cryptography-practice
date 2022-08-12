#sets up the minimum version of cmake
cmake_minimum_required(VERSION 3.9)

project (crypto_practice VERSION 0.1 DESCRIPTION "Some implementations of cryptographic algorithms done for learning purposes.")

set (CMAKE_CXX_STANDARD 20)



add_executable(crypto_practice
    src/pseudorandom/lfsr.cpp
    src/pseudorandom/prng.cpp
    src/pseudorandom/blumblumshub.cpp

    tests/tests.cpp
)


target_compile_options(crypto_practice PRIVATE -Wall -Wextra)

target_include_directories(crypto_practice PUBLIC src/)

