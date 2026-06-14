cmake_minimum_required(VERSION 3.26.0 FATAL_ERROR)

#set(SKIP_APPLE_CHECKS ${APPLE})
#if (APPLE)
#    set(CMAKE_C_COMPILER_WORKS 1)
#    set(CMAKE_CXX_COMPILER_WORKS 1)
#endif ()

project(Quasi CXX)
#set(APPLE 0)

set(CMAKE_CXX_STANDARD 20)

option(ADDITIONAL_FLAGS "additional cmd flags for the compiler" "")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MY_FLAGS}")

if(NOT CMAKE_PLATFORM_NAME)
    set(CMAKE_PLATFORM_NAME "x64")
endif()
message("${CMAKE_PLATFORM_NAME} architecture in use")

if(NOT ("${CMAKE_PLATFORM_NAME}" STREQUAL "x64"
     OR "${CMAKE_PLATFORM_NAME}" STREQUAL "x86"))
    message(FATAL_ERROR "${CMAKE_PLATFORM_NAME} arch is not supported!")
endif()

add_subdirectory(OpenGLPort)
add_subdirectory(Quasi)
