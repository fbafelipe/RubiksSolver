cmake_minimum_required(VERSION 2.8)

PROJECT(RUBIKS_SOLVER)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

ADD_EXECUTABLE(rubiksSolver ${SRCS})
ADD_EXECUTABLE(rubiksSolver-dbg ${SRCS})

SET_TARGET_PROPERTIES(rubiksSolver PROPERTIES COMPILE_FLAGS " -O3 -Wall -DNDEBUG")
SET_TARGET_PROPERTIES(rubiksSolver-dbg PROPERTIES COMPILE_FLAGS " -g -Wall")

