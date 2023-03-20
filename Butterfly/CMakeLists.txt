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
add_subdirectory(third-party/Glad/)

#iclude imgui
add_subdirectory(third-party/ImGui/)

# include spdlog
add_subdirectory(third-party/spdlog/)

#include glm
add_subdirectory(third-party/glm/)

file(GLOB SRC
 "src/*.h"
 "src/*.cpp"
 "src/Butterfly/*.h"
 "src/Butterfly/*.cpp"
 "src/Butterfly/Events/.h*"
 "src/Butterfly/Events/.cpp*"
 "src/Butterfly/ImGui/*.h"
 "src/Butterfly/ImGui/*.cpp"
 "src/Butterfly/Renderer/*.h"
 "src/Butterfly/Renderer/*.cpp"
 "src/Platform/*.h"
 "src/Platform/*.cpp"
 "src/Platform/OpenGL/*.h"
 "src/Platform/OpenGL/*.cpp"
 "third-party/stb/*.h"
 "third-party/stb/*.cpp")

set(LIB_NAME butterfly)

add_definitions(-DGLFW_INCLUDE_NONE)

add_library(${LIB_NAME} STATIC ${SRC})
set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${LIB_NAME} glad glfw spdlog glm imgui)
target_include_directories(${LIB_NAME} PRIVATE src third-party/ImGui third-party/stb third-party/tinyobj)
