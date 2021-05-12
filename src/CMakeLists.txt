
add_library(CGGL SHARED
    Shader.cpp
    ShaderProgram.cpp
    VertexArray.cpp
    VertexBuffer.cpp
    ElementBuffer.cpp
    Texture2D.cpp
    Window.cpp
)

add_library(STBIMAGE SHARED
    stb_image.cpp
)

target_include_directories(STBIMAGE PUBLIC ../include/)

target_include_directories(CGGL PUBLIC ../include/)
add_gl(CGGL)
