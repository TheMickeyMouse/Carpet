cmake_minimum_required(VERSION 4.0)
project(Carpet)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Quasi)
add_subdirectory(OpenGLPort)
add_executable(Carpet main.cpp
        App.cpp
        App.h
        Sys.cpp
        Sys.h
        SDFRenderer.cpp
        SDFRenderer.h
        SDF.cpp
        SDF.h
        Common.h
        GlassRenderer.cpp
        GlassRenderer.h)
target_link_libraries(Carpet PUBLIC Quasi)