cmake_minimum_required(VERSION 3.5.1)
project(dataCompression)
enable_testing()
set(DsSrc
        bit.h bit.cc
        bitree.cc bitree.h
        pqueue.h heap.cc heap.h)
add_library(ds ${DsSrc})
add_executable(bit_test bit_test.cc)
target_link_libraries(bit_test ds)

set(huffmanSrc
        huffman.cc
        compress.h)
add_library(huffman ${huffmanSrc})
target_link_libraries(huffman ds)
add_executable(huffman_test huffman_test.cc)
target_link_libraries(huffman_test huffman)

set(lz77Src
        lz77.cc
        compress.h)
add_library(lz77 ${lz77Src})
target_link_libraries(lz77 ds)
add_executable(lz77_test lz77_test.cc)
target_link_libraries(lz77_test lz77)