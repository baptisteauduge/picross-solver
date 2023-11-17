#include <iostream>
#include <fstream>
#include <chrono>
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

using namespace tomographie;

int main(int argc, char **argv) {
    std::string filename;
    tomographie::ListSequence seq_line;
    tomographie::ListSequence seq_column;


    if (check_args(argc, argv))
        return 1;
    filename = argv[1];
    if (!handle_file(filename, seq_line, seq_column))
        return 1;
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    tomographie::Tomographie tomographie(seq_line, seq_column);

    bool is_possible = tomographie.enumeration();

    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    auto time_taken_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    double time_taken_s = (double) time_taken_ms.count() / 1000.0;

    std::cout << "Time taken by program is : " << time_taken_s;
    std::cout << " sec " << std::endl;
    std::cout << "Is grid successfully filled : " << (int) is_possible << std::endl;

    tomographie.get_grid().print_grid();
    return 0;
}
