# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.24
cmake_policy(SET CMP0009 NEW)

# SOURCES at CMakeLists.txt:10 (file)
file(GLOB NEW_GLOB LIST_DIRECTORIES true "/home/max/Documents/blockchain/src/*.cpp")
set(OLD_GLOB
  "/home/max/Documents/blockchain/src/block.cpp"
  "/home/max/Documents/blockchain/src/blockchain.cpp"
  "/home/max/Documents/blockchain/src/hash.cpp"
  "/home/max/Documents/blockchain/src/main.cpp"
  "/home/max/Documents/blockchain/src/transaction.cpp"
  "/home/max/Documents/blockchain/src/user.cpp"
  "/home/max/Documents/blockchain/src/utils.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/max/Documents/blockchain/cmake-build-release/CMakeFiles/cmake.verify_globs")
endif()
