cmake_minimum_required(VERSION 4.1)
project(DataSorter)

set(CMAKE_CXX_STANDARD 20)

find_package(Threads REQUIRED)

add_executable(DataSorter
        src/main.cpp
        src/server.cpp
        src/Sorter.cpp
)

target_include_directories(DataSorter PRIVATE include/ external/)
target_link_libraries(DataSorter PRIVATE Threads::Threads ws2_32 mswsock)