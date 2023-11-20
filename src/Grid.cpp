//
// Created by Baptiste Audugé on 04/10/2023.
//

#include "Grid.h"
#include <vector>
#include <iostream>

namespace tomographie {

    Grid::Grid (int n, int m, CellColor default_color): grid(std::vector(n, std::vector(m, default_color))),
    size(std::make_pair(n, m)){
    }

    Grid::Grid (const Grid &other): size(other.size), grid(other.grid) {
    }

    Grid::Grid (): Grid(0, 0) {
    }

    bool Grid::is_empty_or_match_line(int line, int i, int j, CellColor color) {
        for (; i < j; ++i) {
            if (grid[line][i] != CellColor::EMPTY && grid[line][i] != color) return false;
        }
        return true;
    }

    bool Grid::is_empty_or_match_col(int col, int i, int j, CellColor color) {
        for (; i < j; ++i) {
            if (grid[i][col] != CellColor::EMPTY && grid[i][col] != color) return false;
        }
        return true;
    }

    bool Grid::line_can_contain_sequence(int j, int l, Sequence &seq) {
        if (!l) return true;
        if (j < seq[l-1] - 1) return false;
        if (j == seq[l-1] - 1) return l == 1;
        return (Grid::line_can_contain_sequence(j - seq[l - 1] - 1, l - 1, seq)
        || Grid::line_can_contain_sequence(j - 1, l, seq));
    }


    bool Grid::line_can_contain_sequence_gen(int line, int j, int l, Sequence &seq) {
        if (!l) return is_empty_or_match_line(line, 0, j + 1, CellColor::WHITE);
        if (j < seq[l-1] - 1) return false;
        if (j == seq[l-1] - 1) return l == 1 && is_empty_or_match_line(line, 0, j + 1, CellColor::BLACK);
        return (
                (is_empty_or_match_line(line, j - seq[l-1] + 1, j + 1 , CellColor::BLACK)
                // Checking if the separator (WHITE) is available
                && is_empty_or_match_line(line, j - seq[l - 1], j - seq[l - 1] + 1, CellColor::WHITE)
                && line_can_contain_sequence_mem(line, j - seq[l - 1] - 1, l - 1, seq, false))
                ||
                (is_empty_or_match_line(line, j, j + 1, CellColor::WHITE)
                && line_can_contain_sequence_mem(line, j - 1, l, seq, false))
                );
    }

    bool Grid::line_can_contain_sequence_mem(int line, int j, int l, Sequence &seq, bool reset_cache) {
        if (reset_cache) cache_contain_line.clear();
        auto cached = cache_contain_line.find({j, l});
        if (cached != cache_contain_line.end())
            return cached->second;
        bool res = line_can_contain_sequence_gen(line, j, l, seq);
        cache_contain_line.insert({{j, l}, res});
        return res;
    }

    bool Grid::column_can_contain_sequence_gen(int column, int j, int l, Sequence &seq) {
        if (!l) return is_empty_or_match_col(column, 0, j + 1, CellColor::WHITE);
        if (j < seq[l-1] - 1) return false;
        if (j == seq[l-1] - 1)
            return l == 1 && is_empty_or_match_col(column, 0, j + 1, CellColor::BLACK);
        return (
                (is_empty_or_match_col(column, j - seq[l-1] + 1, j + 1 , CellColor::BLACK)
                 // Checking if the separator (WHITE) is available
                 && is_empty_or_match_col(column, j - seq[l - 1], j - seq[l - 1] + 1, CellColor::WHITE)
                 && column_can_contain_sequence_mem(column, j - seq[l - 1] - 1, l - 1, seq, false))
                ||
                (is_empty_or_match_col(column, j, j + 1, CellColor::WHITE)
                 && column_can_contain_sequence_mem(column, j - 1, l, seq, false))
        );
    }

    bool Grid::column_can_contain_sequence_mem(int column, int j, int l, Sequence & seq, bool reset_cache) {
        if (reset_cache) cache_contain_col.clear();
        auto cached = cache_contain_col.find({j, l});
        if (cached != cache_contain_col.end())
            return cached->second;
        bool res = column_can_contain_sequence_gen(column, j, l, seq);
        cache_contain_col.insert({{j, l}, res});
        return res;
    }

    GridSize Grid::get_size() {
        return size;
    }

    void Grid::set_cell(int line, int col, CellColor value) {
        grid[line][col] = value;
    }

    CellColor Grid::get_cell(int line, int col) {
        return grid[line][col];
    }


    void Grid::print_grid() {
        for (auto &line: grid) {
            for (auto &cell: line) {
                if (cell == CellColor::EMPTY)
                    std::cout << EMPTY_SYMBOL;
                if (cell == CellColor::BLACK)
                    std::cout << BLACK_SYMBOL;
                if (cell == CellColor::WHITE)
                    std::cout << WHITE_SYMBOL;
            }
            std::cout << std::endl;
        }
    }

    Grid Grid::get_empty_grid() {
        return {0, 0};
    }

    bool Grid::is_full() {
        for (auto &line: grid) {
            for (auto &cell: line) {
                if (cell == CellColor::EMPTY)
                    return false;
            }
        }
        return true;
    }

} // tomographie