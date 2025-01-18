cmake_minimum_required(VERSION 3.29)
project(blg222ehw4 C)

set(CMAKE_C_STANDARD 11)

add_executable(blg222ehw4
        include/min_heap.h
        include/process.h
        include/scheduler.h
        src/main.c
        src/min_heap.c
        src/process.c
        src/scheduler.c)
