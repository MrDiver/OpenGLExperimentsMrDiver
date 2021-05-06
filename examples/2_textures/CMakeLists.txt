
project(2_textures)


set(APP_SOURCES 
    0_first_texture.cpp
    1_active_texture.cpp
)

set(SOURCES
    ../../src/stb_image.cpp
    ../../src/Shader.cpp
    ../../src/ShaderProgram.cpp
)
set(HEADER 
    ../../include/stb_image.hpp
    ../../include/Shader.hpp
    ../../include/ShaderProgram.hpp
)

set(SHADER
    vertex.vert
    fragment.frag
    fragment_active.frag
)

foreach( testsourcefile ${APP_SOURCES} )
    get_filename_component(EXECUTABLE_NAME ${testsourcefile} NAME_WE)
    add_executable( ${EXECUTABLE_NAME} ${testsourcefile} ${SOURCES} ${HEADER})
    set_target_dir(${EXECUTABLE_NAME} ${PROJECT_NAME})
    target_include_directories(${EXECUTABLE_NAME} PUBLIC ../../include)
    foreach(S ${SHADER})
        file(COPY ${S} DESTINATION ${CMAKE_BINARY_DIR}/bin/${PROJECT_NAME}/shader)
    endforeach(S ${SHADER})
    file(COPY ../../res/ DESTINATION ${CMAKE_BINARY_DIR}/bin/${PROJECT_NAME}/res)
    # Make sure YourLib is linked to each app
    add_gl(${EXECUTABLE_NAME})
endforeach( testsourcefile ${APP_SOURCES} )



# add_executable(0_first_triangle 0_first_triangle.cpp)
# add_gl(0_first_triangle)
