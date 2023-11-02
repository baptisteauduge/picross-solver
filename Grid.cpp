//
// Created by Baptiste Audugé on 04/10/2023.
//

#include "Grid.h"
#include <vector>
#include <cassert>
namespace tomographie {

    Grid::Grid (int n, int m, GridColors default_color) {
        grid = std::vector(n, std::vector(m, default_color));
    }

    bool Grid::is_empty_or_match(int line, int i, int j, GridColors color) {
        assert(i <= j);
        for (; i < j; ++i) {
            if (grid[line][i] != EMPTY && grid[line][i] != color) return false;
        }
        return true;
    }

     bool Grid::line_can_contain_sequence(int j, int l, std::vector<int> &seq) {
         assert(l >= 0);
         if (!l) return true;
         if (j < seq[l-1] - 1) return false;
         if (j == seq[l-1] - 1) return l == 1;
         return (Grid::line_can_contain_sequence(j - seq[l - 1] - 1, l - 1, seq)
         || Grid::line_can_contain_sequence(j - 1, l, seq));
     }


    bool Grid::line_can_contain_sequence_gen(int line, int j, int l, std::vector<int> &seq) {
        assert(l >= 0);
        if (!l) return true;
        if (j < seq[l-1] - 1) return false;
        if (j == seq[l-1] - 1) {
            return l == 1 && is_empty_or_match(line, 0, j + 1, BLACK);
        }
        return (
                (Grid::is_empty_or_match(line, j - seq[l-1] + 1, j + 1 , BLACK)
                // Checking if the separator (WHITE) is available
                && Grid::is_empty_or_match(line, j - seq[l - 1], j - seq[l - 1] + 1, WHITE)
                && Grid::line_can_contain_sequence_gen(line, j - seq[l - 1] - 1, l - 1, seq))
                ||
                (Grid::is_empty_or_match(line, j, j + 1, WHITE)
                && Grid::line_can_contain_sequence_gen(line, j - 1, l, seq))
                );
    }

} // tomographie