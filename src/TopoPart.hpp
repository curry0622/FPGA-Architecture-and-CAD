#include <bits/stdc++.h>

class TopoPart {
public:
    // Variables
    int num_fpgas;
    int num_fpga_conns;
    int capacity;
    int num_nodes;
    int num_nets;
    int num_fixed_nodes;

    // Constructors
    TopoPart(std::string file_input, std::string file_output);

    // Methods
    void read_input(std::string file_input);
    void write_output(std::string file_output);

    // Utils
    void pause();
};
