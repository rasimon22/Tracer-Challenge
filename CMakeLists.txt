cmake_minimum_required(VERSION 3.13)
project(Tracer_Challenge)

set(CMAKE_CXX_STANDARD 17)

set(TEST Test/catch.hpp Test/TupleTest.cpp)

set(PRIMITIVES src/Primitives/Tuple.h src/Primitives/Tuple.cpp)

set(SOURCE main.cpp ${TEST} ${PRIMITIVES})

add_executable(Tracer_Challenge ${SOURCE})