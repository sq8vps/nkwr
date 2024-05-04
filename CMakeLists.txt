cmake_minimum_required(VERSION 3.0.0)
project(nkwr VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(nkwr main.cpp graph.cpp dijkstra.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
