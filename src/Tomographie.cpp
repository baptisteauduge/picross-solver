//
// Created by Baptiste Audugé on 06/11/2023.
//

#include "Tomographie.h"
#include <vector>
#include <iostream>

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

    bool Tomographie::color_lines_rec(int curr_line, int curr_col, std::set<int> &new_cols_to_see, Grid &curr_grid) {
        bool is_white, is_black;
        if (curr_line >= num_line || curr_col >= num_col) {
            return true;
        }
        if (curr_grid.get_cell(curr_line, curr_col) != CellColor::EMPTY) {
            return color_lines_rec(curr_line, curr_col + 1, new_cols_to_see, curr_grid);
        }
        curr_grid.set_cell(curr_line, curr_col, CellColor::WHITE);
        is_white = curr_grid.line_can_contain_sequence_gen(curr_line, num_col - 1, (int) line_seq[curr_line].size(),
                                                      line_seq[curr_line]);
        curr_grid.set_cell(curr_line, curr_col, CellColor::BLACK);
        is_black = curr_grid.line_can_contain_sequence_gen(curr_line, num_col - 1, (int) line_seq[curr_line].size(),
                                                      line_seq[curr_line]);
        if (is_black && is_white) {
            curr_grid.set_cell(curr_line, curr_col, CellColor::EMPTY);
            return color_lines_rec(curr_line, curr_col + 1, new_cols_to_see, curr_grid);
        }
        if (is_white) {
            curr_grid.set_cell(curr_line, curr_col, CellColor::WHITE);
            new_cols_to_see.insert(curr_col);
            return color_lines_rec(curr_line, curr_col + 1, new_cols_to_see, curr_grid);
        }
        if (is_black) {
            new_cols_to_see.insert(curr_col);
            return color_lines_rec(curr_line, curr_col + 1, new_cols_to_see, curr_grid);
        }
        return false;
    }

    bool Tomographie::color_lines_rec(int curr_line, int curr_col, std::set<int> &new_cols_to_see) {
        return color_lines_rec(curr_line, curr_col, new_cols_to_see, grid);
    }

    bool Tomographie::color_cols_rec(int curr_line, int curr_col, std::set<int> &new_lines_to_see, Grid &curr_grid) {
        bool is_white, is_black;
        if (curr_line >= num_line || curr_col >= num_col) {
            return true;
        }
        if (curr_grid.get_cell(curr_line, curr_col) != CellColor::EMPTY) {
            return color_cols_rec(curr_line + 1, curr_col, new_lines_to_see, curr_grid);
        }
        curr_grid.set_cell(curr_line, curr_col, CellColor::WHITE);
        is_white = curr_grid.column_can_contain_sequence_gen(curr_col, num_line - 1, (int) col_seq[curr_col].size(),
                                                        col_seq[curr_col]);
        curr_grid.set_cell(curr_line, curr_col, CellColor::BLACK);
        is_black = curr_grid.column_can_contain_sequence_gen(curr_col, num_line - 1, (int) col_seq[curr_col].size(),
                                                        col_seq[curr_col]);
        if (is_black && is_white) {
            curr_grid.set_cell(curr_line, curr_col, CellColor::EMPTY);
            return color_cols_rec(curr_line + 1, curr_col, new_lines_to_see, curr_grid);
        }
        if (is_white) {
            curr_grid.set_cell(curr_line, curr_col, CellColor::WHITE);
            new_lines_to_see.insert(curr_line);
            return color_cols_rec(curr_line + 1, curr_col, new_lines_to_see, curr_grid);
        }
        if (is_black) {
            new_lines_to_see.insert(curr_line);
            return color_cols_rec(curr_line + 1, curr_col, new_lines_to_see, curr_grid);
        }
        return false;
    }

    bool Tomographie::color_cols_rec(int curr_line, int curr_col, std::set<int> &new_lines_to_see) {
        return color_cols_rec(curr_line, curr_col, new_lines_to_see, grid);
    }

    TriState Tomographie::color() {
        std::set<int> lines_to_see = init_range(num_line);
        std::set<int> cols_to_see = init_range(num_col);
        while (!lines_to_see.empty() || !cols_to_see.empty()) {
            std::set<int> new_cols_to_see;
            std::set<int> new_lines_to_see;
            for (auto curr_line: lines_to_see) {
                if (!color_lines_rec(curr_line, 0, new_cols_to_see))
                    return TriState::False;
            }
            lines_to_see.clear();
            cols_to_see.insert(new_cols_to_see.begin(), new_cols_to_see.end());
            new_cols_to_see.clear();
            for (auto curr_col: cols_to_see) {
                if (!color_cols_rec(0, curr_col, new_lines_to_see))
                    return TriState::True;
            }
            cols_to_see.clear();
            lines_to_see.insert(new_lines_to_see.begin(), new_lines_to_see.end());
            new_lines_to_see.clear();
        }
        if (grid.is_full())
            return TriState::True;
        return TriState::Unknown;
    }

    bool Tomographie::enumeration() {
        TriState isColored = color();
        if (isColored == TriState::False)
            return false;
        Grid copy_grid = grid;
        std::pair<bool, Grid> res = enumeration_rec(copy_grid, 0, CellColor::WHITE);
        if (!res.first) {
            copy_grid = grid;
            res =  enumeration_rec(copy_grid, 0, CellColor::BLACK);
            if (res.first)
                grid = res.second;
        } else
            grid = res.second;
        return res.first;
    }

    std::pair<bool, Grid> Tomographie::enumeration_rec(Grid &curr_grid, int k, CellColor c) {
        if (k == num_line * num_line)
            return std::make_pair(true, curr_grid);
        int i = (k/num_col), j = k % num_col;
        TriState resColorPropagate = color_propagate(curr_grid, i, j, c);
        if (resColorPropagate == TriState::True)
            return std::make_pair(true, curr_grid);
        else if (resColorPropagate == TriState::False)
            return std::make_pair(false, Grid::get_empty_grid());
        Grid copy_grid = curr_grid;
        std::pair<bool, Grid> resEnumRec = enumeration_rec(copy_grid, k+1, CellColor::WHITE);
        if (resEnumRec.first) {
            return resEnumRec;
        }
        return enumeration_rec(curr_grid, k+1, CellColor::BLACK);
    }

    TriState Tomographie::color_propagate(Grid &curr_grid, int i, int j, CellColor c) {
        if (curr_grid.get_cell(i, j) != CellColor::EMPTY)
            return TriState::Unknown;
        std::set<int> lines_to_see = {i};
        std::set<int> cols_to_see = {j};
        curr_grid.set_cell(i, j, c);
        while (!lines_to_see.empty() || !cols_to_see.empty()) {
            std::set<int> new_cols_to_see;
            std::set<int> new_lines_to_see;
            for (auto curr_line: lines_to_see) {
                if (!color_lines_rec(curr_line, 0, new_cols_to_see, curr_grid))
                    return TriState::False;
            }
            lines_to_see.clear();
            cols_to_see.insert(new_cols_to_see.begin(), new_cols_to_see.end());
            new_cols_to_see.clear();
            for (auto curr_col: cols_to_see) {
                if (!color_cols_rec(0, curr_col, new_lines_to_see, curr_grid))
                    return TriState::False;
            }
            cols_to_see.clear();
            lines_to_see.insert(new_lines_to_see.begin(), new_lines_to_see.end());
            new_lines_to_see.clear();
        }
        if (curr_grid.is_full())
            return TriState::True;
        return TriState::Unknown;
    }
}
