#include "algo.hpp"
#include <climits>

/**
 * @brief Calculate longest paths to each vertex recursively
 * @param vertex Starting vertex
 */
static void CalculatePathLengths(Vertex &vertex)
{
    /********************************
     * Do a modified recursive deep-first search.
     * We need to check the same vertex multiple times when there are multiple paths leading to the given vertex,
     * so do not keep the "visited" state. The graph is acyclic anyway, so we should never end in an infinite loop.
     ********************************/
    for(auto child : vertex.edges)
    {
        //calculate new path weight, i.e., the parent weight + the child value
        //if it is bigger, that is, the new paths cost is higher, then replace the cost
        //and do a deeper recursive search
        //otherwise skip the child
        long long int weight = vertex.weight + child.get().value;
        if(child.get().weight < weight)
        {
            child.get().weight = weight;
            CalculatePathLengths(child);
        }
    }
}


Vertex* FindLongestPath(Graph &graph)
{
    //start recursive path cost calculation from (1,1)
    graph.at(0).at(0).weight = 0;
    CalculatePathLengths(graph.at(0).at(0));

    //simply find the biggest path cost element
    long long int distance = LONG_LONG_MIN;
    Vertex *farthest = nullptr;
    for(auto &row : graph)
    {
        for(auto &vertex : row)
        {
            if(vertex.weight > distance)
            {
                distance = vertex.weight;
                farthest = &vertex;
            }
        }
    }
    return farthest;
}