#include "TopoPart.hpp"

TopoPart::TopoPart(std::string file_input, std::string file_output) {
    // Read input
    read_input(file_input);



    // Write output
    write_output(file_output);
}

void TopoPart::read_input(std::string file_input) {
    // Variables
    std::ifstream fin(file_input);
    std::stringstream ss;
    std::string line;

    // Read first line
    std::cout << "Read first line:" << std::endl;
    std::getline(fin, line);
    ss << line;
    ss >> num_fpgas >> num_fpga_conns >> capacity >> num_nodes >> num_nets >> num_fixed_nodes;
    std::cout << "# FPGAs: " << num_fpgas << std::endl;
    std::cout << "# FPGA connections: " << num_fpga_conns << std::endl;
    std::cout << "Capacity: " << capacity << std::endl;
    std::cout << "# Nodes: " << num_nodes << std::endl;
    std::cout << "# Nets: " << num_nets << std::endl;
    std::cout << "# Fixed nodes: " << num_fixed_nodes << std::endl;
    ss.clear();
    pause();

    // Read fpga connection channels
    std::cout << "Read fpga connection channels:" << std::endl;
    for(int i = 0; i < num_fpga_conns; i++) {
        std::getline(fin, line);
        ss << line;
        int fpga1, fpga2;
        ss >> fpga1 >> fpga2;
        std::cout << "FPGA1: " << fpga1 << " FPGA2: " << fpga2 << std::endl;
        ss.clear();
    }
    pause();

    // Read nets
    std::cout << "Read nets:" << std::endl;
    for(int i = 0; i < num_nets; i++) {
        std::getline(fin, line);
        ss << line;
        int src, sink;
        ss >> src;
        std::cout << "Src: " << src << " ";
        while(ss >> sink) {
            std::cout << "Sink: " << sink << " ";
        }
        std::cout << std::endl;
        ss.clear();
    }
    pause();

    // Read fixed nodes
    std::cout << "Read fixed nodes:" << std::endl;
    for(int i = 0; i < num_fixed_nodes; i++) {
        std::getline(fin, line);
        ss << line;
        int node, fpga;
        ss >> node >> fpga;
        std::cout << "Node: " << node << " FPGA: " << fpga << std::endl;
        ss.clear();
    }
    pause();
}

void TopoPart::write_output(std::string file_output) {
    // TODO
}

void TopoPart::pause() {
    std::cin.ignore();
}
