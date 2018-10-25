cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 11)
project(socket_4a)
add_executable(socket_4a  tunnel.h socket_4a.cc)
target_link_libraries(socket_4a   muduo_net muduo_base pthread)


add_executable(balancer tunnel.h balancer.cc)
target_link_libraries(balancer  muduo_net muduo_base pthread)