#pragma once

#include "graph.hpp"

/**
 * @brief Find the longest path graph vertex using modified recusrive DFS
 * @param graph Directed acyclic graph
 * @return Pointer to the highest cost vertex
 */
Vertex* FindLongestPath(Graph &graph);