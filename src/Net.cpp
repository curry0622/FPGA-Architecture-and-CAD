#include "Net.hpp"
#include "Node.hpp"

Net::Net() {
    src = nullptr;
    sinks = {};
}

Net::Net(Node* src, int index) {
    this->src = src;
    this->index = index;
    sinks = {};
}

void Net::add_sink(Node* sink) {
    sinks.push_back(sink);
}

void Net::print() {
    std::cout << "[Net]" << std::endl;
    std::cout << "Index: " << index << std::endl;
    std::cout << "Source: " << src->index << std::endl;
    std::cout << "Sinks: ";
    for(const auto& sink : sinks) {
        std::cout << sink->index << " ";
    }
    std::cout << std::endl;
}