cmake_minimum_required(VERSION 2.8)

PROJECT(TEST)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

file(GLOB_RECURSE test_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE SRCS ${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp)

list(REMOVE_ITEM SRCS ${CMAKE_CURRENT_SOURCE_DIR}/../src/main.cpp)

ADD_EXECUTABLE(test ${test_SRCS} ${SRCS})
SET_TARGET_PROPERTIES(test PROPERTIES COMPILE_FLAGS " -g -Wall")
target_link_libraries(test cppunit)
 
