cmake_minimum_required(VERSION 3.9)
project(aal)

set(CMAKE_CXX_STANDARD 14)

add_executable(aal main.cpp generator.h generator.cpp Naive.h Naive.cpp BFS.cpp BFS.h AStar.cpp AStar.h)