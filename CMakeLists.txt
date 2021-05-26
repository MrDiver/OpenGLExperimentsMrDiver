cmake_minimum_required(VERSION 3.13.4)
project(MainProject)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(BUILD_RPATH_USE_ORIGIN TRUE)
# add_compile_definitions(GLFW_INCLUDE_NONE TRUE)

add_compile_definitions(DEBUG)

macro(add_gl EXECUTABLE_NAME)
    target_include_directories(${EXECUTABLE_NAME}
        PUBLIC external/glfw/include
        PUBLIC external/glad/include
    )

    target_link_directories(${EXECUTABLE_NAME}
        PRIVATE external/glfw/src
        PRIVATE external/glad/src
    )

    target_link_libraries(${EXECUTABLE_NAME} glfw glad GL X11 pthread Xrandr Xi dl)
endmacro(add_gl)

function(set_target_dir TARGET SUBDIR)
    set_target_properties( ${TARGET}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${SUBDIR}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${SUBDIR}"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${SUBDIR}"
    )
endfunction(set_target_dir TARGET SUBDIR)


add_subdirectory(examples/0_hello_triangle/)
add_subdirectory(examples/1_shaders/)
add_subdirectory(examples/2_textures/)
add_subdirectory(examples/3_transformations/)

subdirs(
    external/glfw
    external/glad
    external/glm
    src/
)

