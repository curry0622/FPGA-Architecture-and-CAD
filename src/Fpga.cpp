#include "Fpga.hpp"
#include "Node.hpp"

Fpga::Fpga() {
    index = -1;
    capacity = -1;
    max_dist = -1;
    nodes = {};
    neighbors = {};
    dist_sets = {};
}

Fpga::Fpga(int index, int capacity) {
    this->index = index;
    this->capacity = capacity;
    max_dist = -1;
    nodes = {};
    neighbors = {};
    dist_sets = {};
}

bool Fpga::add_node(Node* node) {
    if(nodes.size() == capacity)
        return false;
    nodes[node->index] = node;
    return true;
}

void Fpga::add_neighbor(Fpga* fpga) {
    neighbors.push_back(fpga);
}

void Fpga::print() {
    std::cout << "[FPGA]" << std::endl;
    std::cout << "Index: " << index << std::endl;
    std::cout << "Capacity: " << capacity << std::endl;
    std::cout << "Nodes: ";
    if(nodes.size() == 0) {
        std::cout << "None";
    }
    for(const auto& node : nodes) {
        std::cout << node.second->index << " ";
    }
    std::cout << std::endl;
    std::cout << "Neighbors: ";
    for(const auto& neighbor : neighbors) {
        std::cout << neighbor->index << " ";
    }
    std::cout << std::endl;
    std::cout << "Dist Sets: ";
    for(const auto& dist_set : dist_sets) {
        std::cout << "{";
        for(const auto& fpga : dist_set) {
            std::cout << fpga->index << ",";
        }
        std::cout << "} ";
    }
    std::cout << std::endl;
}
