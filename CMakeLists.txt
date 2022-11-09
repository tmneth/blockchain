cmake_minimum_required(VERSION 3.4)
project(blockchain)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-O3)

include_directories(include)

include_directories(/usr/include/json)

file(GLOB SOURCES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(bin ${SOURCES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fopenmp")

target_link_libraries(bin PUBLIC /usr/lib/libjsoncpp.so)