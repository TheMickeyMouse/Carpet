set(PROJECT_NAME Quasi)

set(HEADER_FILES
    src/Utils/Debug/internal_debug_break.h
    src/Utils/Debug/Logger.h
    src/Utils/Debug/Timer.h

    src/Graphics/GLs/IndexBuffer.h
    src/Graphics/GLs/VertexBuffer.h
    src/Graphics/GLs/Render.h
    src/Graphics/GLs/Shader.h
    src/Graphics/GLs/VertexArray.h
    src/Graphics/GLs/VertexBufferLayout.h
    src/Graphics/GLs/VertexElement.h
    src/Graphics/GLs/FrameBuffer.h
    src/Graphics/GLs/GLDebug.h
    src/Graphics/GLs/GLObject.h
    src/Graphics/GLs/GLTypeID.h
    src/Graphics/GLs/RenderBuffer.h
    src/Graphics/GLs/VertexBlueprint.h
    src/Graphics/GLs/TextureConstants.h
    src/Graphics/GLs/Texture.h

    src/Graphics/GraphicsDevice.h
    src/Graphics/Mesh.h
    src/Graphics/RenderData.h
    src/Graphics/RenderObject.h
    src/Graphics/Triplet.h
    src/Graphics/CameraController2D.h
    src/Graphics/CameraController3D.h
    src/Graphics/Light.h

    src/Graphics/GUI/Canvas.h
    src/Graphics/GUI/UIVertex.h

    src/Graphics/Effects/Bloom.h

    src/Graphics/ModelLoading/MTLMaterialLoader.h
    src/Graphics/ModelLoading/OBJModel.h
    src/Graphics/ModelLoading/OBJModelLoader.h
    src/Graphics/Fonts/Font.h
    src/Graphics/Fonts/FontDevice.h
    src/Graphics/Fonts/TextAlign.h
    src/Graphics/Meshes/MeshBuilder.h
    src/Graphics/GUI/ImGuiExt.h

    src/IO/IO.h

    src/Utils/Math/Constants.h
    src/Utils/Math/Matrix.h
    src/Utils/Math/Rect.h
    src/Utils/Math/Vector.h
    src/Utils/Math/Geometry.h
    src/Utils/Math/Angles.h
    src/Utils/Math/Random.h
    src/Utils/Math/Color.h
    src/Utils/Math/Complex.h
    src/Utils/Math/Quaternion.h
    src/Utils/Math/Transform2D.h
    src/Utils/Math/Transform3D.h

    src/Physics/World2D.h
    src/Physics/Shape2D.h
    src/Physics/Body2D.h
    src/Physics/Collision2D.h
    src/Physics/Manifold2D.h
    src/Physics/SeperatingAxisSolver.h
    src/Physics/CircleShape2D.h
    src/Physics/CapsuleShape2D.h
    src/Physics/PolygonShape2D.h
    src/Physics/RectShape2D.h

    src/Utils/Text.h
    src/Utils/Option.h
    src/Utils/Macros.h
    src/Utils/Type.h
    src/Utils/Match.h
    src/Utils/Memory.h
    src/Utils/Iterator.h
    src/Utils/Vec.h
    src/Utils/Span.h
    src/Utils/Algorithm.h
    src/Utils/Array.h
    src/Utils/Comparison.h
    src/Utils/Box.h
    src/Utils/ArrayBox.h
    src/Utils/Str.h
    src/Utils/String.h
    src/Utils/CStr.h
    src/Utils/Numeric.h
    src/Utils/Tuple.h
    src/Utils/Bitwise.h
    src/Utils/Hash.h
    src/Utils/HashMap.h
    src/Utils/Range.h
    src/Utils/MacroIteration.h
    src/Utils/Text/Parsing.h
    src/Utils/Text/Num.h
    src/Utils/Text/StringWriter.h
    src/Utils/Text/Formatting.h
    src/Utils/Iter/MapIter.h
    src/Utils/Iter/EnumerateIter.h
    src/Utils/Iter/LinesIter.h
    src/Utils/Iter/SplitIter.h
    src/Utils/IO/Archive.h

    src/vendor/imgui/imconfig.h
    src/vendor/imgui/imgui.h
    src/vendor/imgui/imgui_impl_glfw.h
    src/vendor/imgui/imgui_impl_opengl3.h
    src/vendor/imgui/imgui_internal.h
    src/vendor/imgui/imstb_rectpack.h
    src/vendor/imgui/imstb_textedit.h
    src/vendor/imgui/imstb_truetype.h
    src/vendor/imgui/imgui_stdlib.h

    src/vendor/stb_image/stb_image.h
)
source_group("Header Files" FILES ${HEADER_FILES})

set(SOURCE_FILES
    src/Utils/Debug/Logger.cpp
    src/Utils/Debug/Timer.cpp

    src/Graphics/GLs/FrameBuffer.cpp
    src/Graphics/GLs/GLDebug.cpp
    src/Graphics/GLs/RenderBuffer.cpp
    src/Graphics/GLs/IndexBuffer.cpp
    src/Graphics/GLs/VertexBuffer.cpp
    src/Graphics/GLs/VertexArray.cpp
    src/Graphics/GLs/VertexBufferLayout.cpp
    src/Graphics/GLs/Render.cpp
    src/Graphics/GLs/Shader.cpp
    src/Graphics/GLs/Texture.cpp

    src/Graphics/CameraController2D.cpp
    src/Graphics/CameraController3D.cpp
    src/Graphics/Light.cpp
    src/Graphics/GraphicsDevice.cpp
    src/Graphics/RenderData.cpp
    src/Graphics/GUI/Canvas.cpp

    src/Graphics/Effects/Bloom.cpp

    src/Graphics/Meshes/Circle.cpp
    src/Graphics/Meshes/Cube.cpp
    src/Graphics/Meshes/Sphere.cpp
    src/Graphics/Meshes/Icosphere.cpp
    src/Graphics/Meshes/Quad.cpp
    src/Graphics/Meshes/Plane.cpp
    src/Graphics/Meshes/Capsule.cpp
    src/Graphics/Meshes/Stadium.cpp
    src/Graphics/Meshes/Arrow2D.cpp
    src/Graphics/Meshes/Arrow3D.cpp

    src/Graphics/ModelLoading/MTLMaterialLoader.cpp
    src/Graphics/ModelLoading/OBJModelLoader.cpp
    src/Graphics/ModelLoading/OBJModel.cpp
    src/Graphics/Fonts/Font.cpp
    src/Graphics/Fonts/FontDevice.cpp
    src/Graphics/GUI/ImGuiExt.cpp

    src/IO/IO.cpp

    src/Utils/Math/Vector.cpp
    src/Utils/Math/Matrix.cpp
    src/Utils/Math/Rect.cpp
    src/Utils/Math/Color.cpp
    src/Utils/Math/Complex.cpp
    src/Utils/Math/Quaternion.cpp
    src/Utils/Math/Transform2D.cpp
    src/Utils/Math/Transform3D.cpp

    src/Physics/World2D.cpp
    src/Physics/Shape2D.cpp
    src/Physics/Body2D.cpp
    src/Physics/Collision2D.cpp
    src/Physics/Manifold2D.cpp
    src/Physics/SeperatingAxisSolver.cpp
    src/Physics/CircleShape2D.cpp
    src/Physics/CapsuleShape2D.cpp
    src/Physics/PolygonShape2D.cpp
    src/Physics/RectShape2D.cpp

    src/Utils/Text.cpp
    src/Utils/Str.cpp
    src/Utils/String.cpp
    src/Utils/CStr.cpp
    src/Utils/Memory.cpp
    src/Utils/Bitwise.cpp
    src/Utils/Hash.cpp
    src/Utils/Range.cpp
    src/Utils/Text/Parsing.cpp
    src/Utils/Text/Num.cpp
    src/Utils/Text/StringWriter.cpp
    src/Utils/Text/Formatting.cpp
    src/Utils/Iter/LinesIter.cpp
)
source_group("Source Files" FILES ${SOURCE_FILES})

set(ALL_FILES
    ${HEADER_FILES}
    ${SOURCE_FILES}
        src/Graphics/TextureAtlas.h
        src/Graphics/Image.h
        src/Graphics/TextureAtlas.cpp
        src/Graphics/Image.cpp
        src/Graphics/GUI/Interactable.cpp
        src/Graphics/GUI/Interactable.h
        src/Utils/Continuous.h
        src/IO/Key.h
        src/IO/Key.cpp
        src/Graphics/Geometry.cpp
        src/Graphics/Geometry.h
        src/Utils/Math/Rotor2D.h
        src/Utils/Math/Rotor2D.cpp
        src/Utils/Math/Rotor3D.h
        src/Utils/Math/Rotor3D.cpp
)

add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

target_include_directories(${PROJECT_NAME}
        PRIVATE
    ${PROJECT_SOURCE_DIR}/Dependencies/GLFW/include/
    # /Library/Developer/CommandLineTools/SDKs/MacOSX13.3.sdk/System/Library/Frameworks/
        PUBLIC
    src/
    src/Graphics/
    src/vendor/
    src/vendor/imgui/
    src/vendor/freetype/
    ${PROJECT_SOURCE_DIR}/OpenGLPort/
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    Q_EXT_MATCH_SYNTAX # for cool syntax features for pattern matching
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -pedantic -Wall -Wextra
    -Wcast-align
    -Wctor-dtor-privacy
    -Wdisabled-optimization
    -Wformat=2
    -Winit-self
    -Wmissing-include-dirs
    -Woverloaded-virtual
    -Wstrict-null-sentinel
    -Wstrict-overflow=5
    -Wswitch-default
    -Wundef
    -Werror

    -Wno-strict-overflow # way too buggy and aggresive
    -Wno-unused-but-set-variable
    -Wno-unused-variable # allow empty code paths (ex: not calculating logging info) when optimizing
    -Wno-sign-compare # allow comparing ints to uints
    -Wno-misleading-indentation # too lazy to fix
    -Wno-sizeof-pointer-div # allow sizeof(U) / sizeof(T)
    -Wno-missing-field-initializers # allows not initializing certain fields
    -Wno-dangling-reference # too many false-positives, especially for my Ref<T> class.
    -Wno-unused-parameter # it's simply too annoying.
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    OpenGLPort
    # opengl32.dll
    ${CMAKE_SOURCE_DIR}/Dependencies/GLFW/lib-mingw-w64/libglfw3.a
    ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/freetype/libfreetype.a
    ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/imgui/lib/libimgui.a
    ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/stb_image/lib/libstbimage.a
)
# execute_process()