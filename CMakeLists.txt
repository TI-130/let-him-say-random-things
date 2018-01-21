cmake_minimum_required(VERSION 3.6)
project(AIGrandOpus)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp WordPair.h WordPair.cpp)
add_executable(AIGrandOpus ${SOURCE_FILES})
