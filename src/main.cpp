#include <iostream>
#include <fstream>
#include "../include/Grid.h"
#include "../include/file_to_sequence.h"
#include "../include/Tomographie.h"

bool check_args(int argc, char **argv) {
    if (argc < 1) return true;
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <file>" << std::endl;
        return true;
    }
    return false;
}

bool handle_file(std::string &filename, tomographie::ListSequence &seq_line, tomographie::ListSequence &seq_column) {
    std::cout << "Opening file \"" << filename << "\" ..." << std::endl;
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Unable to open the file \"" << filename << "\", exiting ..." << std::endl;
        return false;
    }
    std::cout << "File opened!" << std::endl;
    tomographie::read_file(file, seq_line, seq_column);
    return true;
}

int main(int argc, char **argv) {
    std::string filename;
    tomographie::ListSequence seq_line;
    tomographie::ListSequence seq_column;

    if (check_args(argc, argv)) {
        return 1;
    }
    filename = argv[1];
    if (!handle_file(filename, seq_line, seq_column)) {
        return 1;
    }
    tomographie::Tomographie tomographie(seq_line, seq_column);
    bool is_possible = tomographie.color();
    std::cout << is_possible << std::endl;
    tomographie.get_grid().print_grid();
    return 0;
}
