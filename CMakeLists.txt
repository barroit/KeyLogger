cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_VERSION 10.0.22631)

project(KeyLogger VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

message(STATUS "Build type is ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_FLAGS "-Wall -Wextra -municode")
set(CMAKE_CXX_FLAGS_RELEASE "-Werror -O3")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")

file(GLOB SOURCES_FILE "*.cpp")

add_executable(keylogger ${SOURCES_FILE})