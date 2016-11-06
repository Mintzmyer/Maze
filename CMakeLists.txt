cmake_minimum_required(VERSION 2.8.12.1)

PROJECT(MazeRunner)
SET(VTK_DIR /home/user/Documents/University\ of\ Oregon/CIS\ 441/VTK6.0.0)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(MazeRunner MazeRunner)

if(VTK_LIBRARIES)
  target_link_libraries(MazeRunner ${VTK_LIBRARIES})
else()
  target_link_libraries(MazeRunner vtkHybrid)
endif()

