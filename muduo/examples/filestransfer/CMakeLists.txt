cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 11)

add_executable(download
        download.cc)
target_link_libraries(download muduo_net muduo_base pthread)


