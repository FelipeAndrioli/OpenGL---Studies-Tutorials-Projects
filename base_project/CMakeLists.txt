cmake_minimum_required(VERSION 3.22)

project(base_opengl_project)

file(GLOB_RECURSE SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

file(GLOB_RECURSE HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
)

add_executable(
    ${PROJECT_NAME}
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

# GLFW Setup
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

# GLM Setup
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm)
target_link_libraries(${PROJECT_NAME} glm)

# GLEW Setup
add_definitions(-DGLEW_STATIC)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glew)
target_link_libraries(${PROJECT_NAME} libglew_static)

# Glad Setup
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glad)
target_link_libraries(${PROJECT_NAME} glad)

# Define project properties
set_property(TARGET ${PROJECT_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/binaries)
set_property(TARGET ${PROJECT_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/binaries)
set_property(TARGET ${PROJECT_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/binaries)
set_property(TARGET ${PROJECT_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_CURRENT_SOURCE_DIR}/binaries)
set_property(TARGET ${PROJECT_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/binaries)
set_property(TARGET ${PROJECT_NAME} PROPERTY OUTPUT_NAME "main")