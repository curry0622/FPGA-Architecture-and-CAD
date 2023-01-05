#include <bits/stdc++.h>

#ifndef NET_HPP
#define NET_HPP
class Node;
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
#endif
