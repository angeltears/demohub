cmake_minimum_required(VERSION 3.9)
project(Crypto)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(sha_1)

add_subdirectory(md5)

add_subdirectory(Des)