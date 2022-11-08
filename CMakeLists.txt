cmake_minimum_required(VERSION 3.4)
project(blockchain)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fopenmp")

file(GLOB SOURCES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(test ${SOURCES})
target_link_libraries(test ${JSONCPP_LIBRARIES})