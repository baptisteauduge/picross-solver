#include <iostream>
#include <fstream>
#include <chrono>
#include "Grid.h"
#include "file_to_sequence.h"
#include "Tomographie.h"
#include "utils.h"

bool check_args(int argc, char **argv) {
    if (argc < 1) return true;
    if (argc < 3 || strlen(argv[1]) != 2 || (argv[1][1] != 'p' && argv[1][1] != 'c')) {
        std::cout << "Usage: <-p|-c> " << argv[0] << " <file>"  << std::endl;
        std::cout << "\t-p : Partial resolution algorithm" << std::endl;
        std::cout << "\t-c : Complete resolution algorithm" << std::endl;
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
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    int is_possible;

    if (check_args(argc, argv))
        return 1;
    filename = argv[2];
    if (!handle_file(filename, seq_line, seq_column))
        return 1;
    start = std::chrono::high_resolution_clock::now();
    tomographie::Tomographie tomographie(seq_line, seq_column);
    if (argv[1][1] == 'p')
        is_possible = (int) tomographie.color();
    else if (argv[1][1] == 'c')
        is_possible = (int) tomographie.enumeration();
    else
        return 1;
    end = std::chrono::high_resolution_clock::now();
    auto time_taken_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    double time_taken_s = (double) time_taken_ms.count() / 1.0e9;

    std::cout << "Time taken by program is : " << std::setprecision(9) << time_taken_s;
    std::cout << " sec " << std::endl;
    std::cout << "Is grid successfully filled : " << is_possible << std::endl;

    tomographie.get_grid().print_grid();
    return 0;
}
