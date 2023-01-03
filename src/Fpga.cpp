#include "Fpga.hpp"

Fpga::Fpga() {
    index = -1;
    capacity = -1;
    nodes = {};
}

Fpga::Fpga(int index, int capacity) {
    this->index = index;
    this->capacity = capacity;
    nodes = {};
}

bool Fpga::add_node(Node* node) {
    if(nodes.size() == capacity)
        return false;
    nodes[node->index] = node;
    return true;
}

void Fpga::print() {
    std::cout << "[FPGA]" << std::endl;
    std::cout << "Index: " << index << std::endl;
    std::cout << "Capacity: " << capacity << std::endl;
    std::cout << "Nodes: ";
    for(const auto& node : nodes) {
        std::cout << node.first << " ";
    }
    std::cout << std::endl;
}
