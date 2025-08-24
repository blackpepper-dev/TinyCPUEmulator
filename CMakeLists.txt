cmake_minimum_required(VERSION 3.10)
project(TinyCPUEmulator VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bins/${CMAKE_SYSTEM_NAME})

file(GLOB SRC_FILES src/*.cpp)
add_executable(Program ${SRC_FILES})


