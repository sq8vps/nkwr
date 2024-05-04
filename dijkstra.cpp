#include "dijkstra.hpp"
#include <climits>

Vertex* DijkstraFindHighestWeight(Matrix<Vertex> &graph, bool respectUsageStatus)
{
    int maxVal = INT_MIN;
    Vertex *max = nullptr;

    for(auto &row : graph)
    {
        for(auto &vertex : row)
        {
            //loop for all vertices and find the highest value
            if((!respectUsageStatus || !vertex.used) && (vertex.weight >= maxVal))
            {
                maxVal = vertex.weight;
                max = &vertex;
            }
        }
    }
    return max;
}

void DijkstraFindHighestCostPaths(Matrix<Vertex> &graph)
{
    //This search is based on Dijkstra algortihm,
    //which normally looks for the lowest-cost path.
    //Here, however, we want to find the last point of the highest-cost path,
    //so all comparisons and initial values are just reversed.
    //Also we don't care about the path itself.

    //we are looking for the biggest cost, so set all costs initially to a minimum value
    for(auto &row : graph)
    {
        for(auto &vertex : row)
            vertex.weight = INT_MIN;
    }

    //cost of the starting point is zero
    graph.at(0).at(0).weight = 0;

    //loop for all vertices
    for(auto &row : graph)
    {
        for(auto &_ : row)
        {
            //find highest cost
            struct Vertex *vertex = DijkstraFindHighestWeight(graph, true);

            //get highest cost vertex
            vertex->used = true;

            //loop for all edges...
            for(auto &edge : vertex->edges)
            {
                //...that were not used previously
                if(!edge.destination->used)
                {
                    //calculate new weight
                    int weight = vertex->weight + edge.weight;
                    //find highest weight
                    if(weight > edge.destination->weight)
                    {
                        //update vertex
                        edge.destination->weight = weight;
                    }
                }
            }
        }
    }
}