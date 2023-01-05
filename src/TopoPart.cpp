#include "TopoPart.hpp"
#include "Node.hpp"
#include "Fpga.hpp"
#include "Net.hpp"

TopoPart::TopoPart(std::string file_input, std::string file_output) {
    // Read input
    read_input(file_input);

    // Initialize distance of nodes and FPGAs
    init_dists();

    // Calculate all pairs shortest path to find min dist
    all_pairs_shortest_path();

    // Calculate max dist of FPGAs
    calc_fpga_max_dist();

    // Build FPGA distance sets
    build_fpga_dist_sets();

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
            dist.push_back(INT_MAX);
        }
        node_dists.push_back(dist);
    }

    // Initialize FPGA distances
    for(int i = 0; i < num_fpgas; i++) {
        std::vector<int> dist;
        for(int j = 0; j < num_fpgas; j++) {
            dist.push_back(INT_MAX);
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

void TopoPart::all_pairs_shortest_path() {
    // Floyd-Warshall algorithm for node distances
    for(int k = 0; k < num_nodes; k++) {
        for(int i = 0; i < num_nodes; i++) {
            for(int j = 0; j < num_nodes; j++) {
                if(i == j)
                    node_dists[i][j] = 0;
                if(node_dists[i][k] == INT_MAX || node_dists[k][j] == INT_MAX)
                    continue;
                if(node_dists[i][k] + node_dists[k][j] < node_dists[i][j]) {
                    node_dists[i][j] = node_dists[i][k] + node_dists[k][j];
                }
            }
        }
    }

    // Floyd-Warshall algorithm for FPGA distances
    for(int k = 0; k < num_fpgas; k++) {
        for(int i = 0; i < num_fpgas; i++) {
            for(int j = 0; j < num_fpgas; j++) {
                if(i == j)
                    fpga_dists[i][j] = 0;
                if(fpga_dists[i][k] == INT_MAX || fpga_dists[k][j] == INT_MAX)
                    continue;
                if(fpga_dists[i][k] + fpga_dists[k][j] < fpga_dists[i][j]) {
                    fpga_dists[i][j] = fpga_dists[i][k] + fpga_dists[k][j];
                }
            }
        }
    }
}

void TopoPart::calc_fpga_max_dist() {
    for(auto& fpga_pair : fpgas) {
        Fpga* fpga = fpga_pair.second;
        int max_dist = 0;
        for(int dist : fpga_dists[fpga->index]) {
            if(dist > max_dist)
                max_dist = dist;
        }
        fpga->max_dist = max_dist;
    }
}

void TopoPart::build_fpga_dist_sets() {
    for(auto& fpga_pair : fpgas) {
        Fpga* fpga = fpga_pair.second;
        for(int i = 0; i <= fpga->max_dist; i++) {
            std::set<Fpga*> dist_set;
            for(int j = 0; j < num_fpgas; j++) {
                if(fpga_dists[fpga->index][j] <= i)
                    dist_set.insert(fpgas[j]);
            }
            fpga->dist_sets.push_back(dist_set);
        }
    }
}

void TopoPart::pause() {
    std::cin.ignore();
}

void TopoPart::print_nodes() {
    for(const auto& node_pair : nodes) {
        Node* node = node_pair.second;
        node->print();
        std::cout << std::endl;
    }
}

void TopoPart::print_fpgas() {
    for(const auto& fpga_pair : fpgas) {
        Fpga* fpga = fpga_pair.second;
        fpga->print();
        std::cout << std::endl;
    }
}

void TopoPart::print_node_dists() {
    std::cout << "Node distances:" << std::endl;
    for(int i = 0; i < num_nodes; i++) {
        for(int j = 0; j < num_nodes; j++) {
            if(node_dists[i][j] == INT_MAX)
                std::cout << "- ";
            else
                std::cout << node_dists[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void TopoPart::print_fpga_dists() {
    std::cout << "FPGA distances:" << std::endl;
    for(int i = 0; i < num_fpgas; i++) {
        for(int j = 0; j < num_fpgas; j++) {
            if(fpga_dists[i][j] == INT_MAX)
                std::cout << "- ";
            else
                std::cout << fpga_dists[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
