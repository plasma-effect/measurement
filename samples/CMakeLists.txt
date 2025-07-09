cmake_minimum_required(VERSION 3.16)
project(MeasureSample LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    PlasmaMeasurement
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.."
)
FetchContent_MakeAvailable(PlasmaMeasurement)

add_executable(samples simple.cpp fixture.cpp typed.cpp named_type.cpp)
target_link_libraries(samples PRIVATE measurement)

add_executable(simple simple.cpp)
target_link_libraries(simple PRIVATE measurement)

add_executable(fixture fixture.cpp)
target_link_libraries(fixture PRIVATE measurement)

add_executable(typed typed.cpp)
target_link_libraries(typed PRIVATE measurement)

add_executable(named_type named_type.cpp)
target_link_libraries(named_type PRIVATE measurement)

add_executable(stress_test stress_test.cpp)
target_link_libraries(stress_test PRIVATE measurement)
add_compile_options("-O3")
