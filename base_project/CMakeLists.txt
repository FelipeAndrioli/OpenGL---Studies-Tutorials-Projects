cmake_minimum_required(VERSION 3.22)

project(base_opengl_project LANGUAGE CXX)

# OpenGL Setup
find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})

# GLFW Setup
set(GLFW_BUILD_DOCS OFF CACHE BOOL  "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL  "" FORCE)
add_subdirectory("dependencies/glfw")

# GLM Setup
set(GLMINCLUDES "dependencies/glm")
get_filename_component(GLMINC_PREFIX "${GLMINCLUDES}" ABSOLUTE)

if (NOT EXISTS ${GLMINC_PREFIX}) 
    message(FATAL_ERROR "Necessary glm headers do not exists: " ${GLMINC_PREFIX})
endif()

include_directories(${GLMINC_PREFIX})

set( GLFW-CMAKE-STARTER-SRC
     main.cpp
     )
     
add_executable( GLFW-CMake-starter WIN32 ${GLFW-CMAKE-STARTER-SRC} )
target_link_libraries( GLFW-CMake-starter ${OPENGL_LIBRARIES} glfw )