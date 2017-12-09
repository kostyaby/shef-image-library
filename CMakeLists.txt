cmake_minimum_required(VERSION 3.6.0)
project(ShefImageLib)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O2 ${CMAKE_CXX_FLAGS}")

find_package(OpenCV REQUIRED)

add_library(ImageLib image.cc opencv_downsampler.cc opencv_utils.cc shef_downsampler.cc)

target_include_directories(ImageLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ImageLib ${OpenCV_LIBS})

add_executable(Demo demo.cc)

target_include_directories(Demo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Demo LINK_PUBLIC ImageLib ${OpenCV_LIBS})
