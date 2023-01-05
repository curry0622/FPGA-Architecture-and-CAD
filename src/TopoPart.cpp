#include "TopoPart.hpp"
#include "Node.hpp"
#include "Fpga.hpp"
#include "Net.hpp"

TopoPart::TopoPart(std::string file_input, std::string file_output) {
    // Read input
    read_input(file_input);

    // Initialize distance of nodes and FPGAs
    init_dists();
    print_node_dists();
    pause();
    print_fpga_dists();
    pause();

    // Write output
    write_output(file_output);
}

void TopoPart::read_input(std::string file_input) {
    // Variables
    std::ifstream fin(file_input);
    std::stringstream ss;
    std::string line;

    // Read first line
    std::getline(fin, line);
    ss << line;
    ss >> num_fpgas >> num_fpga_conns >> capacity >> num_nodes >> num_nets >> num_fixed_nodes;
    ss.clear();

    // Initialize nodes
    for(int i = 0; i < num_nodes; i++) {
        nodes[i] = new Node(i);
    }

    // Initialize FPGAs
    for(int i = 0; i < num_fpgas; i++) {
        fpgas[i] = new Fpga(i, capacity);
    }

    // Read FPGA connection channels
    for(int i = 0; i < num_fpga_conns; i++) {
        std::getline(fin, line);
        int fpga1, fpga2;
        ss << line;
        ss >> fpga1 >> fpga2;
        fpgas[fpga1]->add_neighbor(fpgas[fpga2]);
        fpgas[fpga2]->add_neighbor(fpgas[fpga1]);
        ss.clear();
    }

    // Read nets
    for(int i = 0; i < num_nets; i++) {
        std::getline(fin, line);
        int src, sink;
        ss << line;
        ss >> src;
        Net* net = new Net(nodes[src]);
        while(ss >> sink) {
            net->add_sink(nodes[sink]);
        }
        nets.push_back(net);
        ss.clear();
    }

    // Read fixed nodes
    for(int i = 0; i < num_fixed_nodes; i++) {
        std::getline(fin, line);
        int node, fpga;
        ss << line;
        ss >> node >> fpga;
        nodes[node]->set_fpga(fpgas[fpga]);
        nodes[node]->set_fixed(true);
        fpgas[fpga]->add_node(nodes[node]);
        ss.clear();
    }
}

void TopoPart::write_output(std::string file_output) {
    std::ofstream fout(file_output);
    for(int i = 0; i < num_nodes; i++) {
        fout << nodes[i]->index << " ";
        if(nodes[i]->fpga != nullptr)
            fout << nodes[i]->fpga->index << std::endl;
        else
            fout << -1 << std::endl;
    }
    fout.close();
}

void TopoPart::init_dists() {
    // Initialize node distances
    for(int i = 0; i < num_nodes; i++) {
        std::vector<int> dist;
        for(int j = 0; j < num_nodes; j++) {
            dist.push_back(0);
        }
        node_dists.push_back(dist);
    }

    // Initialize FPGA distances
    for(int i = 0; i < num_fpgas; i++) {
        std::vector<int> dist;
        for(int j = 0; j < num_fpgas; j++) {
            dist.push_back(0);
        }
        fpga_dists.push_back(dist);
    }

    // Update node distances
    for(const auto& net : nets) {
        Node* src = net->src;
        for(const auto& sink : net->sinks) {
            node_dists[src->index][sink->index] = 1;
            node_dists[sink->index][src->index] = 1;
        }
    }

    // Update FPGA distances
    for(const auto& fpga_pair : fpgas) {
        Fpga* fpga1 = fpga_pair.second;
        for(const auto& fpga2 : fpga1->neighbors) {
            fpga_dists[fpga1->index][fpga2->index] = 1;
            fpga_dists[fpga2->index][fpga1->index] = 1;
        }
    }
}

void TopoPart::pause() {
    std::cin.ignore();
}

void TopoPart::print_node_dists() {
    std::cout << "Node distances:" << std::endl;
    for(int i = 0; i < num_nodes; i++) {
        for(int j = 0; j < num_nodes; j++) {
            std::cout << node_dists[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void TopoPart::print_fpga_dists() {
    std::cout << "FPGA distances:" << std::endl;
    for(int i = 0; i < num_fpgas; i++) {
        for(int j = 0; j < num_fpgas; j++) {
            std::cout << fpga_dists[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
