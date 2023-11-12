#include <iostream>
#include <fstream>
#include "Grid.h"
#include "file_to_sequence.h"
#include "Tomographie.h"
#include "utils.h"

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
    time_t start, end;

    if (check_args(argc, argv)) {
        return 1;
    }
    filename = argv[1];
    if (!handle_file(filename, seq_line, seq_column)) {
        return 1;
    }
    time(&start);
    tomographie::Tomographie tomographie(seq_line, seq_column);
//    tomographie::TriState is_possible = tomographie.color();
    bool is_possible = tomographie.enumeration();
    time(&end);
    double time_taken = double(end - start);
    std::cout << "Time taken by program is : " << std::fixed
        << time_taken << std::setprecision(5);
    std::cout << " sec " << std::endl;
    std::cout << (int) is_possible << std::endl;
    tomographie.get_grid().print_grid();
    return 0;
}
