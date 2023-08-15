cmake_minimum_required(VERSION 3.18)
project(magicfix C)

add_executable(magicfix main.c)
target_sources(magicfix PRIVATE magicfix.h audio.h audio.c video.h video.c image.h image.c font.h font.c cJSON.h cJSON.c interface.h interface.c)

# Global Flags
set(CMAKE_C_FLAGS "-Wall")

if(WIN32)
	# MSVC Flags
	set(CMAKE_C_FLAGS "-utf-8")
else()
	# GCC and Clang Flags
	set(CMAKE_C_FLAGS "-Wextra")
	set(CMAKE_C_FLAGS_RELEASE "-O3 -s -w")
	set(CMAKE_C_FLAGS_DEBUG "-g")
endif()