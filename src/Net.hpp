#include <bits/stdc++.h>

#ifndef NET_HPP
#define NET_HPP
class Node;
class Net {
public:
    // Variables
    int index;
    Node* src;
    std::vector<Node*> sinks;

    // Constructors
    Net();
    Net(Node* src, int index);

    // Methods
    void add_sink(Node* sink);
    void make_neighborhood();

    // Utils
    void print();
};
#endif
