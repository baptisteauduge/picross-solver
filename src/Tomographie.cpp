//
// Created by Baptiste Audugé on 06/11/2023.
//

#include "Tomographie.h"
#include <vector>
#include <iostream>

namespace tomographie {

    Tomographie::Tomographie(ListSequence &line_sequence, ListSequence &col_sequence)
            : line_seq(line_sequence), col_seq(col_sequence), num_line((int) line_sequence.size()),
              num_col((int) col_sequence.size()), grid((int) line_sequence.size(), (int) col_sequence.size()) {
    }

    std::set<int> Tomographie::init_range(int size) {
        std::set<int> set;

        for (int i = 0; i < size; ++i)
            set.insert(i);
        return set;
    }

    Grid Tomographie::get_grid() {
        return grid;
    }

    bool Tomographie::color_lines_rec(int curr_line, int curr_col, std::set<int> &new_cols_to_see, Grid &curr_grid) {
        bool is_white, is_black;

        if (curr_line >= num_line || curr_col >= num_col)
            return true;
        if (curr_grid.get_cell(curr_line, curr_col) != CellColor::EMPTY)
            return color_lines_rec(curr_line, curr_col + 1, new_cols_to_see, curr_grid);
        curr_grid.set_cell(curr_line, curr_col, CellColor::WHITE);
        is_white = curr_grid.line_can_contain_sequence_mem(curr_line, num_col - 1, (int) line_seq[curr_line].size(),
                                                      line_seq[curr_line]);
        curr_grid.set_cell(curr_line, curr_col, CellColor::BLACK);
        is_black = curr_grid.line_can_contain_sequence_mem(curr_line, num_col - 1, (int) line_seq[curr_line].size(),
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

        if (curr_line >= num_line || curr_col >= num_col)
            return true;
        if (curr_grid.get_cell(curr_line, curr_col) != CellColor::EMPTY)
            return color_cols_rec(curr_line + 1, curr_col, new_lines_to_see, curr_grid);
        curr_grid.set_cell(curr_line, curr_col, CellColor::WHITE);
        is_white = curr_grid.column_can_contain_sequence_mem(curr_col, num_line - 1, (int) col_seq[curr_col].size(),
                                                        col_seq[curr_col]);
        curr_grid.set_cell(curr_line, curr_col, CellColor::BLACK);
        is_black = curr_grid.column_can_contain_sequence_mem(curr_col, num_line - 1, (int) col_seq[curr_col].size(),
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
                    return TriState::False;
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
        TriState is_colored = color();
        Grid copy_grid = grid;
        std::pair<bool, Grid> res;
        if (is_colored == TriState::True)
            return true;
        if (is_colored == TriState::False)
            return false;
        res = enumeration_rec(copy_grid, 0, CellColor::WHITE);
        if (!res.first) {
            copy_grid = grid;
            res =  enumeration_rec(copy_grid, 0, CellColor::BLACK);
            if (res.first) grid = res.second;
        } else
            grid = res.second;
        return res.first;
    }

    int Tomographie::get_next_k_to_fill(Grid &curr_grid, int k) {
        if (k == num_line * num_col)
            return k;
        int i = (k/num_col), j = k % num_col;
        if (curr_grid.get_cell(i, j) != CellColor::EMPTY)
            return get_next_k_to_fill(curr_grid, k+1);
        return k;
    }

    std::pair<bool, Grid> Tomographie::enumeration_rec(Grid &curr_grid, int k, CellColor c) {
        TriState res_color_propagate;
        Grid copy_grid;
        std::pair<bool, Grid> res_enum_rec;
        if (k == num_line * num_col)
            return std::make_pair(true, curr_grid);
        int i = (k/num_col), j = k % num_col;
        res_color_propagate = color_propagate(curr_grid, i, j, c);
        if (res_color_propagate == TriState::True)
            return std::make_pair(true, curr_grid);
        else if (res_color_propagate == TriState::False)
            return std::make_pair(false, Grid::get_empty_grid());
        copy_grid = curr_grid;
        int next_k = get_next_k_to_fill(copy_grid, k+1);
        res_enum_rec = enumeration_rec(copy_grid, next_k, CellColor::WHITE);
        if (res_enum_rec.first) {
            return res_enum_rec;
        }
        return enumeration_rec(curr_grid, next_k, CellColor::BLACK);
    }

    TriState Tomographie::color_propagate(Grid &curr_grid, int i, int j, CellColor c) {
        std::set<int> lines_to_see = {i};
        std::set<int> cols_to_see = {j};

        curr_grid.set_cell(i, j, c);

        bool n_is_color_possible = !curr_grid.line_can_contain_sequence_mem(i, num_col - 1,
                                                                          (int) line_seq[i].size(),line_seq[i]);
        n_is_color_possible = n_is_color_possible || !curr_grid.column_can_contain_sequence_mem(j, num_line - 1,
                                                                            (int) col_seq[j].size(),col_seq[j]);
        if (n_is_color_possible)
            return TriState::False;
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
