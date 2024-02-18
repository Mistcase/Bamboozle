cmake_minimum_required(VERSION 3.20.3 FATAL_ERROR)

project(bamboozle)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# include Vulkan
find_package(Vulkan REQUIRED)

# include glfw to Bamboozle
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

#include entt
add_subdirectory(third-party/entt/)

#include nlohmann_json
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(third-party/nlohmann_json/)

file(GLOB SRC
 "src/*.h"
 "src/*.cpp"
 "src/Bamboozle/*.h"
 "src/Bamboozle/*.cpp"
 "src/Bamboozle/Events/.h*"
 "src/Bamboozle/Events/.cpp*"
 "src/Bamboozle/ImGui/*.h"
 "src/Bamboozle/ImGui/*.cpp"
 "src/Bamboozle/Renderer/*.h"
 "src/Bamboozle/Renderer/*.cpp"
 "src/Bamboozle/Scene/*.h"
 "src/Bamboozle/Scene/*.cpp"
 "src/Platform/*.h"
 "src/Platform/*.cpp"
 "src/Platform/OpenGL/*.h"
 "src/Platform/OpenGL/*.cpp"
 "src/Platform/Vulkan/*.h"
 "src/Platform/Vulkan/*.cpp"
 "third-party/stb/*.h"
 "third-party/stb/*.cpp")

set(LIB_NAME bamboozle)

add_definitions(-DGLFW_INCLUDE_NONE)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions(-DDEBUG)
endif ()

add_library(${LIB_NAME} STATIC ${SRC})
set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${LIB_NAME} glad glfw spdlog glm imgui nlohmann_json::nlohmann_json Vulkan::Vulkan)
target_include_directories(${LIB_NAME} PRIVATE src third-party/ImGui third-party/stb third-party/tinyobj third-party/entt/src third-party/nlohmann_json/include)

target_compile_definitions(${LIB_NAME} PUBLIC "$<$<CONFIG:DEBUG>:DEBUG>")
