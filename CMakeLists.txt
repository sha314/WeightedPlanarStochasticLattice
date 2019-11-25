cmake_minimum_required(VERSION 3.8)
project(WeightedPlanarStochasticLattice)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.cpp
        src/jitu-vai/wpsl-jitu.cpp
        src/jitu-vai/wpsl-jitu.h
        src/view.cpp src/view.h src/wpsl.cpp src/wpsl.h src/index.cpp src/index.h src/wpsl_network.cpp src/wpsl_network.h)

add_executable(wpsl ${SOURCE_FILES})