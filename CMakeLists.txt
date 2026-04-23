cmake_minimum_required(VERSION 4.1)
project(SHA_practice C)

set(CMAKE_C_STANDARD 23)

add_executable(SHA_practice main.c
        sha256/basic_hashing.c
        sha256/basic_hashing.h)
