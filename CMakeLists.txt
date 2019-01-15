cmake_minimum_required(VERSION 3.13)
project(Tracer_Challenge)

set(CMAKE_CXX_STANDARD 17)

set(TEST Test/catch.hpp Test/TupleTest.cpp Test/CanvasTest.cpp Test/MatrixTest.cpp)

set(PRIMITIVES src/Primitives/Tuple.h src/Primitives/Tuple.cpp src/Primitives/Matrix.cpp src/Primitives/Matrix.h)

set(SIMULATION src/Simulation/Environment.h src/Simulation/Environment.cpp src/Simulation/Projectile.h
        src/Simulation/Projectile.cpp)

set(CANVAS src/Render src/Render/Color.cpp src/Render/Color.h src/Render/Canvas.cpp src/Render/Canvas.h)

set(SOURCE main.cpp ${TEST} ${PRIMITIVES} ${SIMULATION} ${CANVAS})


add_executable(Tracer_Challenge ${SOURCE})