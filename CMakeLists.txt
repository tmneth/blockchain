cmake_minimum_required(VERSION 3.24)
project(blockchain)

add_compile_options(-O3)

set(CMAKE_CXX_STANDARD 23)

include_directories(include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23 -fopenmp")

set(SOURCE_FILES src/main.cpp)
add_executable(openmp_test_clion ${SOURCE_FILES})

file(GLOB SOURCES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(test ${SOURCES})
