cmake_minimum_required(VERSION 3.9)
project(aal)

set(CMAKE_CXX_STANDARD 14)

SET(GCC_COVERAGE_COMPILE_FLAGS "-O4" "-m64")

add_executable(aal main.cpp generator.h generator.cpp Naive.h Naive.cpp BFS.cpp BFS.h AStar.cpp AStar.h Application.cpp Application.h)