cmake_minimum_required(VERSION 3.15)

project(TinyCPUEmulator VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bins/${CMAKE_SYSTEM_NAME})


# Включаем предупреждения
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()


file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")
add_executable(Program ${SRC_FILES})



target_include_directories(Program PRIVATE "${CMAKE_SOURCE_DIR}/include")



if (APPLE)
    message(STATUS "Building on macOS")
elseif (WIN32)
    message(STATUS "Building on Windows")
elseif (UNIX)
    message(STATUS "Building on Linux")
endif()
