cmake_minimum_required(VERSION 3.20.3 FATAL_ERROR)

project(Butterfly)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# include glfw to butterfly
# disable tests, examples...
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(third-party/GLFW/)

# include glad
add_subdirectory(third-party/glad/)

#iclude imgui
add_subdirectory(third-party/imgui/)

# include spdlog
add_subdirectory(third-party/spdlog/)

#include glm
add_subdirectory(third-party/glm/)

file(GLOB SRC
 "src/*"
 "src/Bubble/*"
 "src/Bubble/Events/*"
 "src/Bubble/ImGui/*"
 "src/Bubble/Renderer/*"
 "src/Platform/*"
 "src/Platform/OpenGL/*"
 "src/Platform/Windows/*"
 "third-party/stb/*")

set(LIB_NAME butterfly)

add_definitions(-DGLFW_INCLUDE_NONE)

add_library(${LIB_NAME} ${SRC})
set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${LIB_NAME} glad glfw spdlog glm)
target_include_directories(${LIB_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src third-party/ImGui third-party/stb)
