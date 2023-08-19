cmake_minimum_required(VERSION 3.18)
project(magicfix C)

add_executable(magicfix main.c)
target_sources(magicfix PRIVATE magicfix.h magicfix.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -s -w")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")