#include "Node.hpp"
#include "Fpga.hpp"

Node::Node() {
    index = -1;
    fixed = false;
    fpga = nullptr;
    dist_sets = {};
    cddts = {};
}

Node::Node(int index) {
    this->index = index;
    fixed = false;
    fpga = nullptr;
    dist_sets = {};
    cddts = {};
}

void Node::set_fpga(Fpga* fpga) {
    this->fpga = fpga;
}

void Node::set_fixed(bool fixed) {
    this->fixed = fixed;
}

void Node::add_cddt(Fpga* fpga) {
    cddts.insert(fpga);
}

void Node::print() {
    std::cout << "[Node]" << std::endl;
    std::cout << "Index: " << index << std::endl;
    if(fpga)
        std::cout << "FPGA: " << fpga->index << std::endl;
    else
        std::cout << "FPGA: None" << std::endl;
    std::cout << "Fixed: " << fixed << std::endl;
    std::cout << "Dist Sets: ";
    for(const auto& dist_set : dist_sets) {
        std::cout << "{";
        for(const auto& node : dist_set) {
            std::cout << node->index << ",";
        }
        std::cout << "} ";
    }
    std::cout << std::endl;
    std::cout << "Cddts: {";
    for(const auto& cddt : cddts) {
        std::cout << cddt->index << ", ";
    }
    std::cout << "}" << std::endl;
    std::cout << std::endl;
}
