
project(1_shaders)


set(APP_SOURCES 
    0_first_shader.cpp
)

set(SOURCES
    ../../src/Shader.cpp
    ../../src/ShaderProgram.cpp
)
set(HEADER 
    ../../include/Shader.hpp
    ../../include/ShaderProgram.hpp
)

set(SHADER
    vertex.vert
    fragment.frag
)

foreach( testsourcefile ${APP_SOURCES} )
    get_filename_component(EXECUTABLE_NAME ${testsourcefile} NAME_WE)
    add_executable( ${EXECUTABLE_NAME} ${testsourcefile} ${SOURCES} ${HEADER})
    set_target_dir(${EXECUTABLE_NAME} ${PROJECT_NAME})
    target_include_directories(${EXECUTABLE_NAME} PUBLIC ../../include)
    foreach(S ${SHADER})
        configure_file(${S} ${CMAKE_BINARY_DIR}/bin/${PROJECT_NAME}/${S})
    endforeach(S ${SHADER})
    # Make sure YourLib is linked to each app
    add_gl(${EXECUTABLE_NAME})
endforeach( testsourcefile ${APP_SOURCES} )



# add_executable(0_first_triangle 0_first_triangle.cpp)
# add_gl(0_first_triangle)