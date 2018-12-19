cmake_minimum_required(VERSION 3.5.1)
project(2)

enable_testing()

set(CMAKE_CXX_STANDARD  11)

add_executable( oops
        oops.cc)
target_link_libraries(oops pthread)