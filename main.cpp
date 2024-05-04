#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

template <typename T>
using Vector = std::vector<T>;

template <typename T>
using Matrix = std::vector<Vector<T>>;

struct Vertex;

struct Edge
{
    int weight; //path weight - amount of chease eaten when chosing this path
    struct Vertex *destination; //edge destination vertex
};

struct Vertex
{
    std::pair<int, int> xy; //matrix location
    int cheese; //amount of cheese at this vertex
    Vector<struct Edge> edges; //list of edges going out from this vertex
    bool used; //was this vertex already used during search?
    int weight; //highest traversal cost (amount of cheese eaten) for reaching this vertex
};

static void BuildEdgeList(Matrix<struct Vertex> &graph)
{
    for(int x = 0; x < graph.size(); x++) //loop for vertices rows
    {
        for(int y = 0; y < graph[x].size(); y++) //loop for vertices columns
        {
            struct Vertex *Vertex = &graph[x][y];
            struct Edge *e = nullptr;
            for(int dx = -1; dx <= 1; dx++) //loop for neighboring cells
            {
                for(int dy = -1; dy <= 1; dy++)
                {
                    //delta X and Y equal to 0, neigbhor would be pointing to the vertex itself
                    if((dx == 0) && (dy == 0))
                        continue;

                    //check if inside the matrix
                    if(((x + dx) >= 0) && ((x + dx) < graph.size())
                    && ((y + dy) >= 0) && ((y + dy) < graph[x].size()))
                    {
                        //get neighbor
                        struct Vertex *neighbor = &graph[x + dx][y + dy];
                        //find edge directed to the neighbor
                        if(neighbor->cheese >= Vertex->cheese)
                        {
                            struct Edge e;
                            //weight is the difference between the amount of cheese
                            e.weight = neighbor->cheese - Vertex->cheese;
                            e.destination = neighbor;
                            Vertex->edges.push_back(e);
                        }
                    }
                }
            }
        }
    }
}

static Vertex* FindHighestWeight(Matrix<Vertex> &graph, bool respectUsageStatus)
{
    int maxVal = INT_MIN;
    Vertex *max = nullptr;

    for(auto &row : graph)
    {
        for(auto &vertex : row)
        {
            //loop for all vertices and find the highest value
            if((!respectUsageStatus || !vertex.used) && (maxVal < vertex.weight))
            {
                maxVal = vertex.weight;
                max = &vertex;
            }
        }
    }
    return max;
}

int main(int argc, char **argv)
{
    Matrix<struct Vertex> graph; //input matrix/graph
    int N{0}; //matrix dimension

    //check argument count
    if(argc < 2)
    {
        std::cout << "Input file must be specified\n" << std::endl;
        return 0;
    }

    //open file specified by the argument
    std::ifstream file(argv[1]);

    //check if file is open
    if(!file.is_open())
    {
        std::cout << "Failed to open " << argv[1] << std::endl;
        return 0;
    }

    //get data line by line
    std::string line;
    int rows{0}, cols{0};
    while(std::getline(file, line))
    {
        cols = 0;
        //create empty row
        graph.push_back(Vector<Vertex>());
        //get row reference
        auto &row = graph.back();
        //use istringstream to get space separated numbers
        std::istringstream s(line);
        int n{}; //number/cell value
        while(s >> n)
        {
            //fill vertex structure
            struct Vertex v;
            v.xy.first = rows + 1;
            v.xy.second = cols + 1;
            v.weight = 0;
            v.edges.clear();
            v.cheese = n;
            v.used = false;
            //add vertex to the row
            row.push_back(v);
            cols++;
        }
        //check if row lengths are matching
        if((N != 0) && (N != cols))
        {
            file.close();
            std::cout << "Input matrix is broken" << std::endl;
            return 0;
        }
        else
            N = cols; //store row length
        
        rows++;
    }

    file.close();

    //check if matrix is a square matrix
    if(N != graph.size())
    {
        std::cout << "Input matrix is not a square matrix" << std::endl;
        return 0;
    }

    //build edge list from vertices
    BuildEdgeList(graph);
    
    //loop for all vertices
    for(auto &row : graph)
    {
        for(auto &_ : row)
        {
            //find highest cost
            struct Vertex *vertex = FindHighestWeight(graph, true);

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

    // debug part for printing the amount of cheese eaten
    // for(auto &row : graph)
    // {
    //     for(auto &vertex : row)
    //     {
    //         std::cout << vertex.weight << " ";
    //     }
    //     std::cout << std::endl;
    // }

    auto &coordinates = FindHighestWeight(graph, false)->xy;
    
    std::cout << "Chase ends at (" << coordinates.first << ", " << coordinates.second << ")" << std::endl;

    return 0;
}
