cmake_minimum_required(VERSION 3.24.0)

project(Dwarfmatic VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW build documentation" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW build tests" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "GLFW build examples" FORCE)

add_subdirectory(thirdparty/glfw)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        src/main.cpp    
        src/application.cpp
        src/glfw_window.cpp
        src/rendering/shader.cpp
        src/rendering/texture.cpp
        thirdparty/glad/src/glad.c
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        thirdparty/glfw/include
        thirdparty/glad/include
        thirdparty/glm
)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw ${GLFW_LIBRARIES})