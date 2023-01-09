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
    std::vector<std::unordered_set<Node*>> dist_sets;
    std::unordered_set<Fpga*> cddts;

    // Constructors
    Node();
    Node(int index);

    // Methods
    void set_fpga(Fpga* fpga);
    void set_fixed(bool fixed);
    void add_cddt(Fpga* fpga);

    // Utils
    void print();
};
#endif
