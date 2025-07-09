cmake_minimum_required(VERSION 3.16)
project(PlasmaMeasurement LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(measurement src/measure_main.cpp src/measurement_base.cpp)
target_include_directories(measurement PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
