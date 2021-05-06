
project(0_hello_triangle)


set(APP_SOURCES 
    0_first_triangle.cpp
    1_minimal_triangle.cpp
    2_EBO_triangle.cpp
    3_Exercise_2Triangles1VBO.cpp
    4_Exercise_2Triangles2VBO.cpp
    5_Exercise_Take2.cpp
)

set(SOURCES
)
set(HEADER 
)

foreach( testsourcefile ${APP_SOURCES} )
    get_filename_component(EXECUTABLE_NAME ${testsourcefile} NAME_WE)
    add_executable( ${EXECUTABLE_NAME} ${testsourcefile} ${SOURCES} ${HEADER})
    set_target_dir(${EXECUTABLE_NAME} ${PROJECT_NAME})
    # Make sure YourLib is linked to each app
    add_gl(${EXECUTABLE_NAME})
endforeach( testsourcefile ${APP_SOURCES} )



# add_executable(0_first_triangle 0_first_triangle.cpp)
# add_gl(0_first_triangle)