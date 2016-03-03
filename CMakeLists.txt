cmake_minimum_required(VERSION 3.0)
project(readline)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

include_directories(include)
file(GLOB SOURCES "src/*.cpp")
add_executable(readlinetest ${SOURCES})

find_package(Readline REQUIRED)
include_directories(${Readline_INCLUDE_DIR})
target_link_libraries(readlinetest ${Readline_LIBRARY})
