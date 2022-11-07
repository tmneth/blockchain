cmake_minimum_required(VERSION 3.4)
project(blockchain)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fopenmp")

file(GLOB SOURCES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(test ${SOURCES})