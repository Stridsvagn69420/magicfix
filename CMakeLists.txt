cmake_minimum_required(VERSION 3.18)
project(magicfix C)

add_executable(magicfix main.c)
target_sources(magicfix PRIVATE magicfix.h magicfix.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
if (NOT WIN32 AND DEFINED $ENV{CC_NATIVE})
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native")
endif()

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -s -w")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")
