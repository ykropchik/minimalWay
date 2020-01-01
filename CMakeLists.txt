cmake_minimum_required(VERSION 3.15)
project(nameSpaces)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_definitions(-std=gnu++17 -U__STRICT_ANSI__)

set(LINKER_FLAGS1 -lcygwin)
set(LINKER_FLAGS2 -lSDL2main)
set(LINKER_FLAGS3 -lSDL2)
set(LINKER_FLAGS4 -mwindows)

add_subdirectory(googletest)

include_directories(src) # необходимо для того, чтобы писать в директиве просто lib.h
include_directories(googletest/googletest/include)

add_executable(nameSpaces main.cpp src/readFile.cpp src/findMin.cpp src/lib.h)
add_executable(tests tests.cpp src/readFile.cpp src/findMin.cpp)

target_link_libraries(tests gtest)