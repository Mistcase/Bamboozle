cmake_minimum_required(VERSION 3.20.3 FATAL_ERROR)

project(Sandbox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# include glfw to butterfly
# disable tests, examples...
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(EXECUTABLE_NAME Sandbox)

file(GLOB SRC
 "src/*.h"
 "src/*.cpp")

add_executable(${EXECUTABLE_NAME}
    ${SRC})

set_target_properties(${EXECUTABLE_NAME} PROPERTIES
    MACOSX_BUNDLE True
    MACOSX_BUNDLE_GUI_IDENTIFIER my.domain.style.identifier.${EXECUTABLE_NAME}
    MACOSX_BUNDLE_BUNDLE_NAME ${EXECUTABLE_NAME}
    MACOSX_BUNDLE_BUNDLE_VERSION "0.1"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "0.1"
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/cmake/Info.plist)

target_include_directories(${EXECUTABLE_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/../Butterfly/src/
    ${CMAKE_SOURCE_DIR}/../Butterfly/src
    ${CMAKE_SOURCE_DIR}/../Butterfly/third-party/spdlog/include
    ${CMAKE_SOURCE_DIR}/../Butterfly/third-party/glm
    ${CMAKE_SOURCE_DIR}/../Butterfly/third-party/ImGui)

add_subdirectory(../Butterfly/ ../Butterfly/build/)

target_link_libraries(${EXECUTABLE_NAME} butterfly glad glfw spdlog glm imgui)