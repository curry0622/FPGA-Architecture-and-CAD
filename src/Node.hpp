#include <bits/stdc++.h>

#ifndef NODE_HPP
#define NODE_HPP
class Fpga;
class Node {
public:
    // Variables
    int index;
    bool fixed;
    Fpga* fpga;
    std::vector<std::set<Node*>> dist_sets;

    // Constructors
    Node();
    Node(int index);

    // Methods
    void set_fpga(Fpga* fpga);
    void set_fixed(bool fixed);

    // Utils
    void print();
};
#endif
