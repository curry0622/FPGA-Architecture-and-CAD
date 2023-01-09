#include "Node.hpp"
#include "Fpga.hpp"
#include "Net.hpp"

Node::Node() {
    index = -1;
    fixed = false;
    fpga = nullptr;
    nets = {};
    dist_set = {};
    cddts = {};
}

Node::Node(int index) {
    this->index = index;
    fixed = false;
    fpga = nullptr;
    nets = {};
    dist_set = {};
    cddts = {};
}

void Node::add_net(Net* net) {
    nets.push_back(net);
}

void Node::set_fpga(Fpga* fpga) {
    if(this->fpga != nullptr) {
        std::cout << index << " WTF" << std::endl;
    }
    this->fpga = fpga;
}

void Node::set_fixed(bool fixed) {
    this->fixed = fixed;
}

void Node::add_cddt(Fpga* fpga) {
    cddts.insert(fpga);
}

void Node::make_dist_set(int d) {
    int i = 1;
    std::queue<Node*> q;
    for(const auto& node : neighbors) {
        q.push(node);
    }
    while(q.size() > 0 && i < d) {
        Node* node = q.front();
        q.pop();
        dist_set.insert(node);
        for(const auto& neighbor : node->neighbors) {
            q.push(neighbor);
        }
        i++;
    }
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

void Node::make_neighbor(std::vector<Node*> nodes) {
    for(const auto& node : nodes) {
        if(node->index != index) {
            neighbors.push_back(node);
        }
    }
}

int Node::get_dist(Node* node) {
    int d = 1;
    std::queue<Node*> q;
    for(const auto& node : neighbors) {
        q.push(node);
    }
    while(q.size() > 0) {
        int n = q.size();
        for(int i = 0; i < n; i++) {
            Node* node = q.front();
            q.pop();
            if(node->index == node->index) {
                return d;
            }
            for(const auto& neighbor : node->neighbors) {
                q.push(neighbor);
            }
        }
        d++;
    }
    return d;
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
    std::cout << "Neighbors: ";
    for(const auto& neighbor : neighbors) {
        std::cout << neighbor->index << ", ";
    }
    std::cout << std::endl;
    std::cout << "Dist Set: {";
    for(const auto& node : dist_set) {
        std::cout << node->index << ", ";
    }
    std::cout << "}" << std::endl;
    std::cout << "Cddts: {";
    for(const auto& cddt : cddts) {
        std::cout << cddt->index << ", ";
    }
    std::cout << "}" << std::endl;
    std::cout << std::endl;
}
