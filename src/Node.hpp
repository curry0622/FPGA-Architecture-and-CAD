#include <bits/stdc++.h>

#ifndef NODE_HPP
#define NODE_HPP
class Fpga;
class Net;
class Node {
public:
    // Variables
    int index;
    bool fixed;
    Fpga* fpga;
    std::vector<Node*> neighbors;
    std::vector<Net*> nets;
    // std::vector<std::set<Node*>> dist_sets;
    std::set<Node*> dist_set;
    std::set<Fpga*> cddts;

    // Constructors
    Node();
    Node(int index);

    // Methods
    void add_net(Net* net);
    void set_fpga(Fpga* fpga);
    void set_fixed(bool fixed);
    void make_dist_set(int d);
    void add_cddt(Fpga* fpga);
    void intersect_cddts(std::set<Fpga*> fpgas);
    void make_neighbor(std::vector<Node*> nodes);
    int get_dist(Node* node);
    int get_cut_size();

    // Utils
    void print();
};
#endif
