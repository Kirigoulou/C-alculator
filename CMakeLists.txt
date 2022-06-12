cmake_minimum_required(VERSION 3.22)
project(Calculator C)

set(CMAKE_C_STANDARD 99)

add_executable(Calculator main.c linked_list.c linked_list.h types.h types.c)