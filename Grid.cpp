//
// Created by Baptiste Audugé on 04/10/2023.
//

#include "Grid.h"
#include <vector>
#include <cassert>

namespace tomographie {
     Grid::Grid (int n, int m, GridColors default_color) {
        grid = std::vector(n, std::vector(m, default_color));
    };

     bool Grid::line_can_contain_sequence(int j, int l, std::vector<int> seq) {
         assert(l >= 0);
         if (!l) return true;
         if (j < seq[l-1] - 1) return false;
         if (j == seq[l-1] - 1) return l == 1;
         return (Grid::line_can_contain_sequence(j - seq[l - 1], l - 1, seq)
         || Grid::line_can_contain_sequence(j - 1, l, seq));
     }

} // tomographie