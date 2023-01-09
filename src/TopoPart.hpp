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
    std::unordered_map<int, Net*> nets;
    std::vector<std::vector<int>> fpga_dists;
    std::vector<std::pair<Node*, Fpga*>> fixed_node_pairs;

    // Constructors
    TopoPart(std::string file_input, std::string file_output);

    // Methods
    void read_input(std::string file_input);
    void write_output(std::string file_output);
    void init_dists();
    void all_pairs_shortest_path();
    void calc_fpga_max_dist();
    void build_fpga_dist_sets();
    void init_cddts();
    void update_cddts();
    void partition();

    // Utils
    void pause();
    void print_nodes();
    void print_fpgas();
    void print_nets();
    void print_fpga_dists();
};
#endif
