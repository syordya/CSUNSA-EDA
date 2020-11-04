cmake_minimum_required(VERSION 3.16)
project( Octree )

# include OpenCV
find_package( OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable( Octree main.cpp )
target_link_libraries( Octree ${OpenCV_LIBS} )
