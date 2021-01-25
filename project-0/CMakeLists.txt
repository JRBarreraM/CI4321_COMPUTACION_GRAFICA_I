# Project definition
cmake_minimum_required(VERSION 3.0)
project(InitGL)

# Source files and libraries paths
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")
set(SOURCES "${SRC_DIR}/main.cpp")

# Executable definition and properties
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")

# Compilation
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# OPENGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

# GLUT
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})
if(NOT GLUT_FOUND)
    message(ERROR "GLUT not found!")
endif(NOT GLUT_FOUND)

target_link_libraries(${PROJECT_NAME} ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})
