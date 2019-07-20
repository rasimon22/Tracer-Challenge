cmake_minimum_required(VERSION 3.13)
project(Tracer_Challenge)

set(CMAKE_CXX_STANDARD 17)

file( GLOB_RECURSE TEST Test/*.cpp)

file( GLOB_RECURSE PRIMITIVES src/Primitives/*/*.cpp )

file( GLOB_RECURSE SIMULATION src/Simulation/*/*.cpp )

file( GLOB_RECURSE CANVAS src/Render/*/*.cpp )

set(SOURCE main.cpp ${TEST} ${PRIMITIVES} ${SIMULATION} ${CANVAS})
add_executable( TESTS ${SOURCE} )


target_include_directories(TESTS
        PUBLIC src/Primitives/Include
        PUBLIC src/Render/Include
        PUBLIC src/Simulation/Include
        PUBLIC Test)



