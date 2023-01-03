#include "Node.hpp"

Node::Node() {
    index = -1;
    fpga = -1;
    fixed = false;
}

Node::Node(int index) {
    this->index = index;
    fpga = -1;
    fixed = false;
}

void Node::set_fpga(int fpga) {
    this->fpga = fpga;
}

void Node::set_fixed() {
    fixed = true;
}

void Node::print() {
    std::cout << "[Node]" << std::endl;
    std::cout << "Index: " << index << std::endl;
    std::cout << "FPGA: " << fpga << std::endl;
    std::cout << " Fixed: " << fixed << std::endl;
}
