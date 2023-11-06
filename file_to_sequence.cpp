//
// Created by Baptiste Audugé on 03/11/2023.
//

#include "file_to_sequence.h"
#include <string>
#include <fstream>
#include "utils.h"

namespace tomographie {
    void get_sequence (std::ifstream  &file, ListSequence &lseq) {
        std::string line ;
        Sequence seq;
        int idx_delimiter;
        std::string seq_str;
        int seq_val;

        std::getline(file, line);
        do {
            line += " ";
            seq = Sequence();
            while (!line.empty()) {
                idx_delimiter = (int) line.find_first_of(SEQ_DELIMITER);
                seq_str = line.substr(0, idx_delimiter);
                if (!seq_str.empty()) {
                    seq_val = std::stoi(seq_str);
                    seq.push_back(seq_val);
                }
                line = line.erase(0, idx_delimiter + 1);
            }
            lseq.push_back(seq);
            std::getline(file, line);
        } while (!file.eof() && line != "#");
    }

    void read_file(std::ifstream &file, ListSequence &seq_line, ListSequence &seq_column) {
        get_sequence(file, seq_line);
        get_sequence(file, seq_column);
    }
}

