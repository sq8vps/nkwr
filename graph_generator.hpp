#pragma once
#include <string>

#define MAX_VALUE 10    // Maximum random value on graph
#define MIN_VALUE 1     // Minimum random value on graph


/**
 * @brief Generate graph on file
 * @param n Graph dimension
 * @return Return 0 on success, -1 on failure
*/
int GraphGenerate(std::string n);
