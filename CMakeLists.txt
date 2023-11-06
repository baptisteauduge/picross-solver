cmake_minimum_required(VERSION 3.26)
project(Tomographie)

set(CMAKE_CXX_STANDARD 17)

add_executable(Tomographie src/main.cpp
        src/Grid.cpp
        include/Grid.h
        src/file_to_sequence.cpp
        include/file_to_sequence.h
        include/utils.h
        src/Tomographie.cpp
        include/Tomographie.h
)
