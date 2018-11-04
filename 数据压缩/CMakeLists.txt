cmake_minimum_required(VERSION 3.5.1)
project(dataCompression)
enable_testing()
set(BitSrc
        bit.h
        bit.cc)

add_library(bit ${BitSrc})


add_executable(bit_test bit_test.cc)
target_link_libraries(bit_test bit)