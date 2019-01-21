cmake_minimum_required(VERSION 3.5.1)

project(fastdfs_demo)



include_directories(/usr/include/fastdfs)
include_directories(/usr/include/fastcommon)
link_libraries(fdfsclient)
link_libraries(fastcommon)
add_executable(Main
        Main.cc fdfs_api.cc
        make_log.cc)



