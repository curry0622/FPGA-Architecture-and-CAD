#include "Node.hpp"
#include "Fpga.hpp"
#include "Net.hpp"

Node::Node() {
    index = -1;
    fixed = false;
    fpga = nullptr;
    nets = {};
    dist_sets = {};
    cddts = {};
}

Node::Node(int index) {
    this->index = index;
    fixed = false;
    fpga = nullptr;
    nets = {};
    dist_sets = {};
    cddts = {};
}

void Node::add_net(Net* net) {
    nets.push_back(net);
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

void Node::intersect_cddts(std::set<Fpga*> fpgas) {
    std::set<Fpga*> tmp;
    std::set_intersection(
        cddts.begin(),
        cddts.end(),
        fpgas.begin(),
        fpgas.end(),
        std::inserter(
            tmp,
            tmp.begin()
        )
    );
    cddts = tmp;
}

int Node::get_cut_size() {
    int cut_size = 0;
    for(const auto& net : nets) {
        std::set<Fpga*> fpgas;
        if(net->src->fpga != nullptr)
            fpgas.insert(net->src->fpga);
        for(const auto& sink : net->sinks) {
            if(sink->fpga != nullptr)
                fpgas.insert(sink->fpga);
        }
        cut_size += fpgas.size();
    }
    return cut_size;
}

void Node::print() {
    std::cout << "[Node]" << std::endl;
    std::cout << "Index: " << index << std::endl;
    if(fpga)
        std::cout << "FPGA: " << fpga->index << std::endl;
    else
        std::cout << "FPGA: None" << std::endl;
    std::cout << "Fixed: " << fixed << std::endl;
    std::cout << "Nets: " << std::endl;
    for(const auto& net : nets) {
        net->print();
    }
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
