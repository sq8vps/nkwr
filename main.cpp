#include <iostream>
#include <string>
#include "graph.hpp"
#include "dijkstra.hpp"
#include "graph_generator.hpp"

int main(int argc, char **argv)
{
    Matrix<struct Vertex> graph; //input matrix/graph
    int N{0}; //square matrix dimension
    
    //check argument count
    if(argc <= 2)
    {
        std::cout << "Input file or dimension must be specified\n" << std::endl;
        return 0;
    }
    else if(argc == 3){
        if(std::string(argv[1]) == "-f"){       // Option -f: read directly from file, Argument: file path
            //read graph from file and store its dimensions
            N = GraphReadFromFile(argv[2], graph);
        }
        else if(std::string(argv[1]) == "-g"){  // Option -g: generate graph nxn, Argument: int n
            //generate graph n x n in file
            if(GraphGenerate(argv[2]) !=0 ){
                std::cout << "Failed to generate graph\n" << std::endl;
                return 0;
            };
            N = GraphReadFromFile( std::string(argv[2]) + "_" + std::string(argv[2]) + ".txt", graph);
        }      
        else{
            std::cout << "Selected invalid option\n" << std::endl;
            return 0;
        }   
    }
    else{
        std::cout << "Invalid arguments\n" << std::endl;
        return 0;
    }

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
