cmake_minimum_required(VERSION 3.24)
project(blockchain)

add_compile_options(-O3)

set(CMAKE_CXX_STANDARD 23)

include_directories(include)

file(GLOB SOURCES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(test ${SOURCES})
