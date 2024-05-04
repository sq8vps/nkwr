#pragma once

#include <vector>
#include <string>

/**
 * @brief Allow edges between diagonal matrix cells
*/ 
//#define GRAPH_ALLOW_DIAGONAL

/**
 * @brief Generic vector helper template
*/
template <typename T>
using Vector = std::vector<T>;

/**
 * @brief Generic matrix helper template
*/
template <typename T>
using Matrix = std::vector<Vector<T>>;

struct Vertex;

/**
 * @brief Graph edge descriptor
*/
struct Edge
{
    int weight; /**< Path weight/cost */
    struct Vertex *destination; /**< Destination vertex */
};

/**
 * @brief Graph vertex descriptor
*/
struct Vertex
{
    std::pair<int, int> xy; /**< Location of this vertex in matrix */
    int value; /**< Vertex value */
    Vector<struct Edge> edges; /**< List of edges going out from this vertex */

    //algorithm-dependent members
    bool used; /**< Was this vertex already used during search? */
    int weight; /**< Calculated traversal cost when reaching this vertex */
};


/**
 * @brief Fill edge list of given matrix-based graph
 * 
 * This function assigns edges to all vertices. The edge is created
 * only if the neighboring (destination) vertex has a bigger value
 * than the source vertex. The edge cost is calculated as the difference
 * between vertex values.
 * Note that \a GRAPH_ALLOW_DIAGONAL must be defined
 * to allow creation of edges between two diagonal cells.
 * @param graph Matrix containing the graph
*/
void GraphBuildEdgeList(Matrix<struct Vertex> &graph);

/**
 * @brief Read matrix from a text file
 * @param path File path
 * @param graph Graph containter
 * @return Matrix dimension (positive) on success, negative value on failure
*/
int GraphReadFromFile(std::string path, Matrix<Vertex> &graph);