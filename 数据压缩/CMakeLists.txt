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
add_executable(main  main.cc)
target_link_libraries(main huffman)