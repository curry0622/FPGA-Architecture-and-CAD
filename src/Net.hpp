#include <bits/stdc++.h>

#ifndef NODE_HPP
#define NODE_HPP
#include "Node.hpp"
#endif

class Net {
public:
    // Variables
    Node* src;
    std::vector<Node*> sinks;

    // Constructors
    Net();
    Net(Node* src);

    // Methods
    void add_sink(Node* sink);

    // Utils
    void print();
};
