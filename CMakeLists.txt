cmake_minimum_required(VERSION 3.9)
project(simple_server C)

set(CMAKE_C_STANDARD 99)

add_executable(simple_server main.c helper.c helper.h)