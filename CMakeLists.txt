cmake_minimum_required(VERSION 3.24.0)

project(Dwarfmatic VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY out)

# glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW build documentation" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "GLFW build tests" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "GLFW build examples" FORCE)

add_subdirectory(thirdparty/glfw)

# assimp
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Assimp build shared libraries" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Assimp build tests" FORCE)
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "Assimp build zlib" FORCE)
set(ASSIMP_INSTALL ON CACHE BOOL "Assimp install" FORCE)

add_subdirectory(thirdparty/assimp)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        src/main.cpp    
        src/application.cpp
        src/glfw_window.cpp
        src/ubo.cpp
        src/scene.cpp
        src/ecs/uuid.cpp
        src/ecs/system_manager.cpp
        src/resource_manager.cpp
        src/rendering/camera.cpp
        src/rendering/camera_manager.cpp
        src/rendering/mesh.cpp
        src/rendering/model.cpp
        src/rendering/shader.cpp
        src/rendering/texture2d.cpp
        src/rendering/point_light.cpp
        src/rendering/spot_light.cpp
        src/rendering/directional_light.cpp
        src/utils/gl_debug.cpp
        src/utils/logging.cpp
        src/utils/profiling.cpp
        thirdparty/glad/src/glad.c
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        src/
        thirdparty/glad/include
        thirdparty/glfw/include
        thirdparty/glm
        thirdparty/assimp/include
        ${CMAKE_CURRENT_BINARY_DIR}/thirdparty/assimp/include
        thirdparty/stb/include
        thirdparty/spdlog/include
        thirdparty/entt/src
)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw ${GLFW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE assimp)

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/resources
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources
    COMMENT "Copying resources into build directory"
)

add_dependencies(${PROJECT_NAME} copy_resources)