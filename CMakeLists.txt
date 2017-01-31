cmake_minimum_required(VERSION 3.6)
project(PSU_2016_malloc)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        lib/libmy_malloc.so
        lib/Makefile
        lib/malloc.c
        lib/malloc.h
        lib/malloc.o
        main.c
        Makefile
        moul_malloc_stud)

add_executable(PSU_2016_malloc ${SOURCE_FILES})