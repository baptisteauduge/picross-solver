//
// Created by Baptiste Audugé on 06/11/2023.
//

#ifndef TOMOGRAPHIE_TOMOGRAPHIE_H
#define TOMOGRAPHIE_TOMOGRAPHIE_H

#include "Grid.h"
#include "utils.h"
#include "vector"
#include <set>

class Tomographie {
private:
    ListSequence line_seq;
    ListSequence col_seq;
    tomographie::Grid grid;
    int num_line;
    int num_col;
    static std::set<int> init_range(int size);
    bool color_lines_rec(int curr_line, int curr_col, std::set<int> &new_cols_to_see);
    bool color_cols_rec(int curr_line, int curr_col, std::set<int> &new_lines_to_see);
public:
    Tomographie(ListSequence &line_sequence, ListSequence &col_sequence);
    tomographie::Grid get_grid();
    bool color();
    void print_grid();
};


#endif //TOMOGRAPHIE_TOMOGRAPHIE_H
