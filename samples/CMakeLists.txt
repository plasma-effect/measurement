cmake_minimum_required(VERSION 3.16)
project(MeasureSample LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
    PlasmaMeasurement
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.."
)
FetchContent_MakeAvailable(PlasmaMeasurement)

add_executable(samples simple.cpp fixture.cpp typed.cpp)
target_link_libraries(samples PRIVATE measurement)
