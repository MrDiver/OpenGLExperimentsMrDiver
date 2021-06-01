
project(3_transformations)

set(APP_SOURCES 
    0_first_transformation.cpp
    1_duplicate_transformation.cpp
    2_spaces_transformation.cpp
    3_cube_army.cpp
    4_camera.cpp
)

set(SHADER
    vertex.vert
    perspective_shader.vert
    fragment.frag
)

foreach( testsourcefile ${APP_SOURCES} )
    # Get filename
    get_filename_component(EXECUTABLE_NAME ${testsourcefile} NAME_WE)
    # Create Executable
    add_executable(${EXECUTABLE_NAME} ${testsourcefile})
    # Set output Directory
    set_target_dir(${EXECUTABLE_NAME} ${PROJECT_NAME})
    # Set include directory
    target_include_directories(${EXECUTABLE_NAME} PUBLIC ../../include)

    # Copy Shader Files
    foreach(S ${SHADER})
        file(COPY ${S} DESTINATION ${CMAKE_BINARY_DIR}/bin/${PROJECT_NAME}/shader)
    endforeach(S ${SHADER})
    file(COPY ../../res/ DESTINATION ${CMAKE_BINARY_DIR}/bin/${PROJECT_NAME}/res)
    # Add Opengl and CGGL Library
    add_gl(${EXECUTABLE_NAME})
    target_link_libraries(${EXECUTABLE_NAME} CGGL STBIMAGE)
endforeach( testsourcefile ${APP_SOURCES} )
