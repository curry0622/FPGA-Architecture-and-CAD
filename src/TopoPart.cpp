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

    // Initialize nodes
    for(int i = 0; i < num_nodes; i++) {
        nodes[i] = new Node(i);
    }

    // Initialize FPGAs
    for(int i = 0; i < num_fpgas; i++) {
        fpgas[i] = new Fpga(i, capacity);
    }

    // Read fpga connection channels
    std::cout << "Read fpga connection channels:" << std::endl;
    for(int i = 0; i < num_fpga_conns; i++) {
        std::getline(fin, line);
        int fpga1, fpga2;
        ss << line;
        ss >> fpga1 >> fpga2;
        std::cout << "FPGA1: " << fpga1 << " FPGA2: " << fpga2 << std::endl;
        ss.clear();
    }

    // Read nets
    std::cout << "Read nets:" << std::endl;
    for(int i = 0; i < num_nets; i++) {
        std::getline(fin, line);
        int src, sink;
        ss << line;
        ss >> src;
        std::cout << "Src: " << src << " ";
        Net* net = new Net(nodes[src]);
        while(ss >> sink) {
            std::cout << "Sink: " << sink << " ";
            net->add_sink(nodes[sink]);
        }
        std::cout << std::endl;
        nets.push_back(net);
        ss.clear();
    }

    // Read fixed nodes
    for(int i = 0; i < num_fixed_nodes; i++) {
        std::getline(fin, line);
        int node, fpga;
        ss << line;
        ss >> node >> fpga;
        nodes[node]->set_fpga(fpga);
        nodes[node]->set_fixed();
        fpgas[fpga]->add_node(nodes[node]);
        ss.clear();
    }

    for(const auto& net : nets) {
        net->print();
    }
}

void TopoPart::write_output(std::string file_output) {
    std::ofstream fout(file_output);
    for(int i = 0; i < num_nodes; i++) {
        fout << nodes[i]->index << " " << nodes[i]->fpga << std::endl;
    }
    fout.close();
}

void TopoPart::pause() {
    std::cin.ignore();
}
