#pragma once

#include <string>

#define MAX_VALUE 20    // Maximum random value on graph
#define MIN_VALUE 1     // Minimum random value on graph

/**
 * @brief Generate graph represented as a matrix and save to file
 * @param n Matrix dimension
 * @return Generated file name or empty string on failure
*/
std::string GraphGenerate(std::string n);
