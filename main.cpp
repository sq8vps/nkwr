#include <iostream>
#include <string>
#include "graph.hpp"
#include "dijkstra.hpp"
#include "graph_generator.hpp"

int main(int argc, char **argv)
{
    std::string path; //file path
    Matrix<struct Vertex> graph; //input matrix/graph
    int N{0}; //square matrix dimension

    //check argument count
    if(argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " [-g <dimension>]/<file>" << std::endl 
            << "Provide input file or use -g <dimension> to generate random matrix" << std::endl;
        return 0;
    }
    else
    {
        if(std::string(argv[1]) == "-g") // Option -g: generate graph nxn, Argument: int n
        {  
            if(argc == 2)
            {
                std::cout << "Matrix dimension must be specified" << std::endl;
                return -1;
            }
            //generate graph n x n in file
            path = GraphGenerate(argv[2]);
            if(path.empty())
            {
                return -1;
            }
        }      
        else
        {
            path = argv[1];
        }   
    }

    std::cout << "Reading from " << path << std::endl;

    N = GraphReadFromFile(path, graph);

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
