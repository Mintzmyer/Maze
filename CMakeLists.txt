cmake_minimum_required(VERSION 2.8.12.1)

PROJECT(MazeRunner)
SET(VTK_DIR "/usr/local/Cellar/vtk/7.1.0_6")

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
link_libraries(${OPENGL_LIBRARIES})


add_executable(MazeRunner MazeRunner.cxx)

if(VTK_LIBRARIES)
  target_link_libraries(MazeRunner ${VTK_LIBRARIES})
else()
  target_link_libraries(MazeRunner vtkHybrid)
endif()

