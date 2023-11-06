//
// Created by Baptiste Audugé on 03/11/2023.
//

#ifndef TOMOGRAPHIE_FILE_TO_SEQUENCE_H
#define TOMOGRAPHIE_FILE_TO_SEQUENCE_H
#include "utils.h"

namespace tomographie {

    #define SEQ_DELIMITER ' '

    /**
     * Get a sequence from a file
     * @param file The file to read
     * @param lseq The list of sequence to append
     */
    void get_sequence (std::ifstream  &file, ListSequence &lseq);

    /**
     * Get sequence columns and line from a file
     * @param file The file to read
     * @param seq_line The list of line sequence to append
     * @param seq_column The list of column sequence to append
     */
    void read_file(std::ifstream &file, ListSequence &seq_line, ListSequence &seq_column);
}

#endif //TOMOGRAPHIE_FILE_TO_SEQUENCE_H
