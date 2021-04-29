cmake_minimum_required(VERSION 3.13.4)

project(PracticeProject)

add_executable(${PROJECT_NAME} src/main.cpp)

subdirs(
    external/glfw
    external/glad
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC external/glfw/include
    PUBLIC external/glad/include
)

target_link_directories(${PROJECT_NAME}
    PRIVATE external/glfw/src
    PRIVATE external/glad/src
)

target_link_libraries(${PROJECT_NAME} glfw glad GL X11 pthread Xrandr Xi dl)