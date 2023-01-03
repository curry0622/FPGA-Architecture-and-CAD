#include <bits/stdc++.h>

#ifndef NODE_HPP
#define NODE_HPP
#include "Node.hpp"
#endif

class Fpga {
public:
    // Variables
    int index;
    int capacity;
    std::unordered_map<int, Node*> nodes;

    // Constructors
    Fpga();
    Fpga(int index, int capacity);

    // Methods
    bool add_node(Node* node);

    // Utils
    void print();
};
