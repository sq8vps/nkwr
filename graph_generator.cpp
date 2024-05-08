#include "graph_generator.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <random>
#include <chrono>

// Function to create and save new graph to file
void save_graph (std::ofstream* file, int n);

int GraphGenerate(std::string n){
    std::string path = n + "_" + n + ".txt"; // File path format "n_n.txt"
    int n_number =0;

    // Conversion input dimension from string to int
    try{                
        n_number = stoi(n);
    }catch(const std::invalid_argument& err) {
        std::cout << "Invalid input argument: " << err.what() <<std::endl;
        return -1;
    } catch(const std::out_of_range& err) {
        std::cout << "Input argument out of range: " << err.what() <<std::endl;
        return -1;
    }

    std::ifstream file(path);
    // Check if file exist
    if(file.good()){
        file.close();
        std::ofstream newFile (path, std::ios::trunc); // Open exist file and clear
        if(!newFile.is_open()){
            std::cout << "Failed to open " << path << std::endl;
            return -1;
        }
        save_graph(&newFile, n_number); // Create and save new graph to file
        newFile.close();
    }
    else{
        file.close();
        std::ofstream newFile (path);  // Create new file
        if(!newFile.is_open()){
            std::cout << "Failed to open " << path << std::endl;
            return -1;
        }
        save_graph(&newFile, n_number); // Create and save new graph to file
        newFile.close();
    }
    return 0;
}

void save_graph (std::ofstream* file, int n){
    // Init random generator
    std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution{ MIN_VALUE, MAX_VALUE };

    // Create and save graph with random value
    for(int y = 0; y < n; y++){
        for(int x = 0; x < n; x++){
            *file << distribution(gen);
            if(x != n-1){
                *file << " ";
            } 
        }
        if(y != n-1){
            *file << std::endl;
        }
    }
}
