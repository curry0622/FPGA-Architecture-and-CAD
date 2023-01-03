#include <bits/stdc++.h>

#ifndef NODE_HPP
#define NODE_HPP
#include "Node.hpp"
#endif

#ifndef FPGA_HPP
#define FPGA_HPP
#include "Fpga.hpp"
#endif

class TopoPart {
public:
    // Variables
    int num_fpgas;
    int num_fpga_conns;
    int capacity;
    int num_nodes;
    int num_nets;
    int num_fixed_nodes;
    std::unordered_map<int, Node*> nodes;
    std::unordered_map<int, Fpga*> fpgas;

    // Constructors
    TopoPart(std::string file_input, std::string file_output);

    // Methods
    void read_input(std::string file_input);
    void write_output(std::string file_output);

    // Utils
    void pause();
};
