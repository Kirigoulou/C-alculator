cmake_minimum_required(VERSION 3.22)
project(Calculator C)

set(CMAKE_C_STANDARD 99)

add_executable(Calculator main.c data_structures/linked_list.c data_structures/linked_list.h types.h
        types.c data_structures/stack.h data_structures/stack.c data_structures/queue.h
               data_structures/queue.c)