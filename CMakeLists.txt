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
    src/GlassRenderer.h
    src/TerrainRenderer.h
    src/TerrainRenderer.cpp
    src/res/Shaders.h
    src/Elements/El.cpp
    src/Elements/El.h
        src/Elements/El.cpp
        src/Elements/WidgetEl.cpp
        src/Elements/WidgetEl.h
        src/Elements/TextEl.cpp
        src/Elements/TextEl.h
        src/Elements/ElMeta.cpp
        src/Elements/ElMeta.h
        src/Elements/UIDoc.cpp
        src/Elements/UIDoc.h
        src/Elements/ElLayout.cpp
        src/Elements/ElLayout.h)
target_link_libraries(Carpet PUBLIC Quasi)