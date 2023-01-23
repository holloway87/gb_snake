cmake_minimum_required(VERSION 3.24)
project(gb_snake C)

set(CMAKE_C_STANDARD 23)

add_executable(gb_snake src/main.c)

target_include_directories(gb_snake PUBLIC ~/Programs/gbdk/include)
