//
// Created by Baptiste Audugé on 04/10/2023.
//

#ifndef TOMOGRAPHIE_GRID_H
#define TOMOGRAPHIE_GRID_H

#include <string>
#include <vector>

namespace tomographie {

    enum GridColors {
        WHITE ,
        BLACK,
        EMPTY
    };

    class Grid {
        private:
            std::vector<std::vector<GridColors>> grid;
        public:
            Grid (int n, int m, GridColors default_color = EMPTY);
            bool line_can_contain_sequence(int j, int l, std::vector<int> seq);
    };

} // tomographie

#endif //TOMOGRAPHIE_GRID_H
