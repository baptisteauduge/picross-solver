//
// Created by Baptiste Audugé on 06/11/2023.
//

#include "Tomographie.h"
#include <vector>

namespace tomographie {

    Tomographie::Tomographie(ListSequence &line_sequence, ListSequence &col_sequence)
            : line_seq(line_sequence), col_seq(col_sequence), num_line((int) line_sequence.size()),
              num_col(col_sequence.size()), grid(line_sequence.size(), col_sequence.size()) {
    }

    std::set<int> Tomographie::init_range(int size) {
        std::set<int> set;
        for (int i = 0; i < size; ++i) {
            set.insert(i);
        }
        return set;
    }

    Grid Tomographie::get_grid() {
        return grid;
    }

    bool Tomographie::color_lines_rec(int curr_line, int curr_col, std::set<int> &new_cols_to_see) {
        bool is_white, is_black;
        if (curr_line >= num_line || curr_col >= num_col) {
            return true;
        }
        if (grid.get_cell(curr_line, curr_col) != EMPTY) {
            return color_lines_rec(curr_line, curr_col + 1, new_cols_to_see);
        }
        grid.set_cell(curr_line, curr_col, WHITE);
        is_white = grid.line_can_contain_sequence_gen(curr_line, num_col - 1, (int) line_seq[curr_line].size(),
                                                      line_seq[curr_line]);
        grid.set_cell(curr_line, curr_col, BLACK);
        is_black = grid.line_can_contain_sequence_gen(curr_line, num_col - 1, (int) line_seq[curr_line].size(),
                                                      line_seq[curr_line]);
        if (is_black && is_white) {
            grid.set_cell(curr_line, curr_col, EMPTY);
            return color_lines_rec(curr_line, curr_col + 1, new_cols_to_see);
        }
        if (is_white) {
            grid.set_cell(curr_line, curr_col, WHITE);
            new_cols_to_see.insert(curr_col);
            return color_lines_rec(curr_line, curr_col + 1, new_cols_to_see);
        }
        if (is_black) {
            new_cols_to_see.insert(curr_col);
            return color_lines_rec(curr_line, curr_col + 1, new_cols_to_see);
        }
        return false;
    }

    bool Tomographie::color_cols_rec(int curr_line, int curr_col, std::set<int> &new_lines_to_see) {
        bool is_white, is_black;
        if (curr_line >= num_line || curr_col >= num_col) {
            return true;
        }
        if (grid.get_cell(curr_line, curr_col) != EMPTY) {
            return color_cols_rec(curr_line + 1, curr_col, new_lines_to_see);
        }
        grid.set_cell(curr_line, curr_col, WHITE);
        is_white = grid.column_can_contain_sequence_gen(curr_col, num_line - 1, (int) col_seq[curr_col].size(),
                                                        col_seq[curr_col]);
        grid.set_cell(curr_line, curr_col, BLACK);
        is_black = grid.column_can_contain_sequence_gen(curr_col, num_line - 1, (int) col_seq[curr_col].size(),
                                                        col_seq[curr_col]);
        if (is_black && is_white) {
            grid.set_cell(curr_line, curr_col, EMPTY);
            return color_cols_rec(curr_line + 1, curr_col, new_lines_to_see);
        }
        if (is_white) {
            grid.set_cell(curr_line, curr_col, WHITE);
            new_lines_to_see.insert(curr_line);
            return color_cols_rec(curr_line + 1, curr_col, new_lines_to_see);
        }
        if (is_black) {
            new_lines_to_see.insert(curr_line);
            return color_cols_rec(curr_line + 1, curr_col, new_lines_to_see);
        }
        return false;
    }


    bool Tomographie::color() {
        std::set<int> lines_to_see = init_range(num_line);
        std::set<int> cols_to_see = init_range(num_col);
        while (!lines_to_see.empty() || !cols_to_see.empty()) {
            std::set<int> new_cols_to_see;
            std::set<int> new_lines_to_see;
            for (auto curr_line: lines_to_see) {
                if (!color_lines_rec(curr_line, 0, new_cols_to_see))
                    return false;
            }
            lines_to_see.clear();
            cols_to_see.insert(new_cols_to_see.begin(), new_cols_to_see.end());
            new_cols_to_see.clear();
            for (auto curr_col: cols_to_see) {
                if (!color_cols_rec(0, curr_col, new_lines_to_see))
                    return false;
            }
            cols_to_see.clear();
            lines_to_see.insert(new_lines_to_see.begin(), new_lines_to_see.end());
            new_lines_to_see.clear();
        }
        return true;
    }

    void Tomographie::print_grid() {
        grid.print_grid();
    }
}
