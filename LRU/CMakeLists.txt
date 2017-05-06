cmake_minimum_required(VERSION 3.7)
project(LRU)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c call.c INT.h INT.c)
add_executable(LRU ${SOURCE_FILES})