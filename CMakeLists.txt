cmake_minimum_required(VERSION 4.0)
project(Carpet)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Quasi)
add_subdirectory(OpenGLPort)
add_executable(Carpet main.cpp
    src/App.cpp
    src/App.h
    src/Sys.cpp
    src/Sys.h
    src/Common.h
    src/GlassRenderer.cpp
    src/GlassRenderer.h)
target_link_directories(Carpet PUBLIC src)
target_link_libraries(Carpet PUBLIC Quasi)