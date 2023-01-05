#include "Node.hpp"
#include "Fpga.hpp"

Node::Node() {
    index = -1;
    fpga = nullptr;
    fixed = false;
}

Node::Node(int index) {
    this->index = index;
    fpga = nullptr;
    fixed = false;
}

void Node::set_fpga(Fpga* fpga) {
    this->fpga = fpga;
}

void Node::set_fixed(bool fixed) {
    this->fixed = fixed;
}

void Node::print() {
    std::cout << "[Node]" << std::endl;
    std::cout << "Index: " << index << std::endl;
    std::cout << "FPGA: " << fpga << std::endl;
    std::cout << "Fixed: " << fixed << std::endl;
}
