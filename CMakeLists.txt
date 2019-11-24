cmake_minimum_required(VERSION 3.8)
project(WeightedPlanarStochasticLattice)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.cpp
        src/wpsl.cpp
        src/wpsl.h
        src/view.cpp src/view.h)

add_executable(wpsl ${SOURCE_FILES})