#include "graph.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <climits>

void GraphBuildEdgeList(Graph &graph)
{
    for(int x = 0; x < graph.size(); x++) //loop for vertices rows
    {
        for(int y = 0; y < graph.at(x).size(); y++) //loop for vertices columns
        {
            struct Vertex &vertex = graph.at(x).at(y);
            struct Edge *e = nullptr;
            for(int dx = -1; dx <= 1; dx++) //loop for neighboring cells
            {
                for(int dy = -1; dy <= 1; dy++)
                {
                    //check if inside the matrix
                    if(((x + dx) >= 0) && ((x + dx) < graph.size())
                    && ((y + dy) >= 0) && ((y + dy) < graph.at(x).size())
#ifdef GRAPH_ALLOW_DIAGONAL
                    //skip zero delta case
                    && (!((dx == 0) && (dy == 0)))
#else
                    //and go only up, down, left or right
                    && (((dx == 0) && (dy != 0)) || ((dx != 0) && (dy == 0)))
#endif
                    )
                    {
                        //get neighbor
                        struct Vertex &neighbor = graph.at(x + dx).at(y + dy);
                        //find edge directed to the neighbor
                        if(neighbor.value > vertex.value)
                        {
                            vertex.edges.push_back(neighbor);
                        }
                    }
                }
            }
        }
    }
}

int GraphReadFromFile(std::string path, Graph &graph)
{
    //open file
    std::ifstream file(path);

    //check if file is open
    if(!file.is_open())
    {
        std::cout << "Failed to open " << path << std::endl;
        return -1;
    }

    //get data line by line
    std::string line;
    int rows{0}, cols{0}; //number of rows and columns
    int lastRowLength{0};
    while(std::getline(file, line))
    {
        cols = 0;
        //create empty row
        graph.push_back(Vector<Vertex>());
        //get row reference
        auto &row = graph.back();
        //use istringstream to get space separated numbers
        std::istringstream s(line);
        int n{}; //cell value
        while(s >> n)
        {
            //fill vertex structure
            struct Vertex v;
            v.xy.first = rows + 1;
            v.xy.second = cols + 1;
            v.weight = INT_MIN;
            v.edges.clear();
            v.value = n;
            v.used = false;
            //add vertex to the row
            row.push_back(v);
            cols++;
        }

        //allow empty rows, just skip them
        if(0 == cols)
        {
            graph.pop_back(); //remove previously added empty row
            continue;
        }

        //check if row lengths are matching
        if((lastRowLength != 0) && (lastRowLength != cols))
        {
            file.close();
            std::cout << "Input matrix is broken" << std::endl;
            return -1;
        }
        else
            lastRowLength = cols; //store row length
        
        rows++;
    }

    file.close();

    //check if matrix is a square matrix
    if(lastRowLength != graph.size())
    {
        std::cout << "Input matrix is not a square matrix" << std::endl;
        return -1;
    }

    if(0 == lastRowLength)
    {
        std::cout << "Input matrix is empty" << std::endl;
        return -1;
    }

    return lastRowLength;
}