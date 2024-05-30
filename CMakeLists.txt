cmake_minimum_required(VERSION 3.5.0)
project(nkwr VERSION 0.1.0 LANGUAGES C CXX)

add_executable(nkwr dijkstra.cpp graph.cpp main.cpp graph_generator.cpp)