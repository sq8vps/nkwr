#include <iostream>
#include <string>
#include "graph.hpp"
#include "dijkstra.hpp"

int main(int argc, char **argv)
{
    Matrix<struct Vertex> graph; //input matrix/graph
    int N{0}; //square matrix dimension

    //check argument count
    if(argc < 2)
    {
        std::cout << "Input file must be specified\n" << std::endl;
        return 0;
    }

    //read graph from file and store its dimensions
    N = GraphReadFromFile(argv[1], graph);
    if(N < 0) //exit on failure
        return -1;

    //build edge list from vertices
    GraphBuildEdgeList(graph);
    
    //calculate path costs using modified Dijkstra algorithm
    DijkstraFindHighestCostPaths(graph);

    //find vertex with the highest cost
    auto &coordinates = DijkstraFindHighestWeight(graph, false)->xy;
    
    std::cout << "Highest cost cell is at (" << coordinates.first << ", " << coordinates.second << ")" << std::endl;

    return 0;
}
