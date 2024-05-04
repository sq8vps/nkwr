#pragma once

#include "graph.hpp"

/**
 * @brief Find vertex with highest weight
 * @param graph Input graph
 * @param respectUsageStatus Skip vertices already used (member \a used set to true)
 * @return Vertex with the highest weight
*/
Vertex* DijkstraFindHighestWeight(Matrix<Vertex> &graph, bool respectUsageStatus);

/**
 * @brief Find highest cost paths for all graph vertices
 * @param graph Input graph
 * @attention All graph edges must be calculated first
 * @attention The search always starts from matrix cell (1, 1)
 * @note This function uses a modified Dijkstra algorithm
*/
void DijkstraFindHighestCostPaths(Matrix<Vertex> &graph);