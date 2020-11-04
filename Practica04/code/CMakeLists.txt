cmake_minimum_required( VERSION 3.16 )
project( OctreeQuantizer )

# include OpenCV
find_package( OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable( OctreeQuantizer main.cpp )
target_link_libraries( OctreeQuantizer ${OpenCV_LIBS} )
