cmake_minimum_required(VERSION 2.8)

project( OpenCV )


# Unterscheidung OS, 
if (WIN32)
	find_package( OpenCV REQUIRED PATHS "D:/OpenCV/opencv/build/x64/vc15/lib")
endif (WIN32)

if (UNIX)
	find_package( OpenCV REQUIRED )
endif (UNIX)
	


# Festlegen wohin die binary kommt, später wichtig für die DLLs unter Windows
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)


include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories("src")
include_directories("include")



add_executable( DisplayImage src/main.cpp src/DisplayImage.cpp src/core_functionality.cpp src/random.cpp)
target_link_libraries( DisplayImage ${OpenCV_LIBS})
