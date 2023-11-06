cmake_minimum_required(VERSION 3.26)
project(Tomographie)

set(CMAKE_CXX_STANDARD 17)

add_executable(Tomographie main.cpp
        Grid.cpp
        Grid.h
        file_to_sequence.cpp
        file_to_sequence.h
        utils.h
        Tomographie.cpp
        Tomographie.h
)
