#include <bits/stdc++.h>

#ifndef TOPOPART_HPP
#define TOPOPART_HPP
class Node;
class Fpga;
class Net;
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
    std::vector<Net*> nets;
    std::vector<std::vector<int>> node_dists;
    std::vector<std::vector<int>> fpga_dists;

    // Constructors
    TopoPart(std::string file_input, std::string file_output);

    // Methods
    void read_input(std::string file_input);
    void write_output(std::string file_output);
    void init_dists();
    void all_pairs_shortest_path();
    void calc_fpga_max_dist();

    // Utils
    void pause();
    void print_node_dists();
    void print_fpga_dists();
};
#endif
