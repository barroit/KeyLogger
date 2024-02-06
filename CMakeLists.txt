cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_VERSION 22H2)

project(KeyLogger VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

message(STATUS "Build type is ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_FLAGS "-Wall -Wextra -municode")
set(CMAKE_CXX_FLAGS_RELEASE "-Werror -O3")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")

configure_file(config.hpp.in config.hpp)

file(GLOB SOURCES_FILE "src/*.cpp")

add_executable(keylogger WIN32 ${SOURCES_FILE} keylogger.rc)

target_include_directories(keylogger PRIVATE ${PROJECT_BINARY_DIR})

target_link_libraries(keylogger comctl32)

target_compile_definitions(keylogger
	PRIVATE UNICODE				# Enable unicode support
	PRIVATE NTDDI_VERSION=NTDDI_WIN10	# Targeting Windows 10
)

target_precompile_headers(keylogger PRIVATE <windows.h> PRIVATE <shellapi.h>)