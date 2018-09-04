cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 11)

set(std=c++11)
add_library(muduo_pubsub pubsub.cc codec.cc)
target_link_libraries(muduo_pubsub muduo_net muduo_base pthread)

add_executable(pub pub.cc)
target_link_libraries(pub muduo_pubsub)

add_executable(sub sub.cc)
target_link_libraries(sub muduo_pubsub)


add_executable(hub hub.cc codec.cc)
target_link_libraries(hub muduo_inspect muduo_net muduo_base pthread)