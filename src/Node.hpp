#include <bits/stdc++.h>

class Node {
public:
    // Variables
    int index;
    int fpga;
    bool fixed;

    // Constructors
    Node();
    Node(int index);

    // Methods
    void set_fpga(int fpga);
    void set_fixed();

    // Utils
    void print();
};
