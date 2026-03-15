set(PROJECT_NAME OpenGLPort)

add_library(${PROJECT_NAME} STATIC glp.h glp.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
    "${PROJECT_SOURCE_DIR}/Dependencies/GLEW/include"
    # "/Library/Developer/CommandLineTools/SDKs/MacOSX13.3.sdk/usr/include"
    .
)

if (SKIP_APPLE_CHECKS)
    set(OPENGL_FRAMEWORK_SET "-framework OpenGL")
else()
    set(OPENGL_FRAMEWORK_SET "C:/Windows/System32/opengl32.dll")
endif()


target_link_libraries(${PROJECT_NAME} PUBLIC
    ${OPENGL_FRAMEWORK_SET}
    ${CMAKE_SOURCE_DIR}/Dependencies/GLEW/lib/libglew32.a
)

target_compile_options(${PROJECT_NAME} PUBLIC -DGLEW_STATIC)

# target_compile_options(${PROJECT_NAME} PUBLIC -v)