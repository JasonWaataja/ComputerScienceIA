cmake_minimum_required(VERSION 3.0)
project(bashtutorial)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

include_directories(include)
file(GLOB SOURCES "src/*.cpp")
add_executable(runbashtutorial ${SOURCES})
set_property(TARGET runbashtutorial PROPERTY CXX_STANDARD 11)

find_package(Readline REQUIRED)
include_directories(${Readline_INCLUDE_DIR})
target_link_libraries(runbashtutorial ${Readline_LIBRARY})
