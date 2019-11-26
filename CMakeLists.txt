cmake_minimum_required(VERSION 3.8)
project(WeightedPlanarStochasticLattice)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.cpp
        src/jitu-vai/wpsl-jitu.cpp
        src/jitu-vai/wpsl-jitu.h
        src/view.cpp src/view.h src/wpsl/wpsl.cpp src/wpsl/wpsl.h src/index/index.cpp src/index/index.h src/wpsl/wpsl_network.cpp src/wpsl/wpsl_network.h src/wpsl/wpsl_network_v2.cpp src/wpsl/wpsl_network_v2.h)

add_executable(wpsl ${SOURCE_FILES})