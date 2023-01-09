#include <bits/stdc++.h>

#ifndef FPGA_HPP
#define FPGA_HPP
class Node;
class Fpga {
public:
    // Variables
    int index;
    int capacity;
    int max_dist;
    std::unordered_map<int, Node*> nodes;
    std::vector<Fpga*> neighbors;
    std::vector<std::unordered_set<Fpga*>> dist_sets;

    // Constructors
    Fpga();
    Fpga(int index, int capacity);

    // Methods
    bool add_node(Node* node);
    void add_neighbor(Fpga* fpga);

    // Utils
    void print();
};
#endif
