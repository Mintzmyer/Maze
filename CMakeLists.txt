cmake_minimum_required(VERSION 2.8.12.1)

PROJECT(MazeGUI)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

add_executable(MazeGUI MazeGUI.cxx)

target_link_libraries(MazeGUI ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})



