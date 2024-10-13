cmake_minimum_required(VERSION 3.16)
project( AprilTag_Detector LANGUAGES CXX )

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
  add_compile_options(-Wall -Wextra)
endif()

find_package( OpenCV REQUIRED )

include_directories(/usr/local/include/apriltag)

find_library(APRILTAG_LIBRARIES NAMES apriltag PATHS /usr/local/lib)

include_directories( ${OpenCV_INCLUDE_DIRS} )

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable( Main src/Main.cpp ${SOURCES} )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

target_link_libraries( Main ${OpenCV_LIBS} ${APRILTAG_LIBRARIES})