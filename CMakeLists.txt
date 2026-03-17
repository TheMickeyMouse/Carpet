cmake_minimum_required(VERSION 4.0)
project(Carpet)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Quasi)
add_subdirectory(OpenGLPort)
add_executable(Carpet main.cpp
        Carpet.cpp
        Carpet.h
        Sys.cpp
        Sys.h)
target_link_libraries(Carpet PUBLIC Quasi)