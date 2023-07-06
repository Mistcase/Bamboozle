cmake_minimum_required(VERSION 3.20.3 FATAL_ERROR)

project(Sandbox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# disable tests, examples...
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(EXECUTABLE_NAME Sandbox)

file(GLOB SRC
 "src/*.h"
 "src/*.cpp")

file(GLOB_RECURSE RESOURCES "${CMAKE_SOURCE_DIR}/res/*")

if (APPLE)
  add_executable(${EXECUTABLE_NAME} ${SRC} ${RESOURCES})
else ()
  add_executable(${EXECUTABLE_NAME} ${SRC})
endif()

message("Output directory: ${CMAKE_BINARY_DIR}")
if(WIN32)
   message("Identified platform: Windows")
   file(COPY "${CMAKE_SOURCE_DIR}/res" DESTINATION "${CMAKE_BINARY_DIR}/")

elseif(APPLE)
   message("Identified platform: OSX")
   foreach (FILE ${RESOURCES})
       # Get the relative path from the res-folder to the particular file.
       file(RELATIVE_PATH NEW_FILE "${CMAKE_SOURCE_DIR}/res/" ${FILE})

       # Get the relative path to the file.
       get_filename_component(NEW_FILE_PATH ${NEW_FILE} DIRECTORY)

       # Set it's location inside the app package (under Resources).
       set_property(SOURCE ${FILE} PROPERTY MACOSX_PACKAGE_LOCATION "Resources/${NEW_FILE_PATH}")
    endforeach ()

    set_target_properties(${EXECUTABLE_NAME} PROPERTIES
    MACOSX_BUNDLE True
    MACOSX_BUNDLE_GUI_IDENTIFIER my.domain.style.identifier.${EXECUTABLE_NAME}
    MACOSX_BUNDLE_BUNDLE_NAME ${EXECUTABLE_NAME}
    MACOSX_BUNDLE_BUNDLE_VERSION "0.1"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "0.1"
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/cmake/Info.plist)

elseif(UNIX)
   message("Identified platform: Linux")
   file(COPY "${CMAKE_SOURCE_DIR}/res" DESTINATION "${CMAKE_BINARY_DIR}/")

 endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions(-DDEBUG)
endif ()

target_include_directories(${EXECUTABLE_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/../Bamboozle/src/
    ${CMAKE_SOURCE_DIR}/../Bamboozle/src
    ${CMAKE_SOURCE_DIR}/../Bamboozle/third-party/spdlog/include
    ${CMAKE_SOURCE_DIR}/../Bamboozle/third-party/glm
    ${CMAKE_SOURCE_DIR}/../Bamboozle/third-party/ImGui
    ${CMAKE_SOURCE_DIR}/../Bamboozle/third-party/entt/src)

add_subdirectory(../Bamboozle/ ../../Bamboozle/build/)

target_link_libraries(${EXECUTABLE_NAME} bamboozle glad glfw spdlog glm imgui)
