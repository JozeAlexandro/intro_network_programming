cmake_minimum_required(VERSION 3.5)

project(counter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options( -Wall -Wextra -Wpedantic -Werror -O3 )

add_executable( counter main.cpp )
