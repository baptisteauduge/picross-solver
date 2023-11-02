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
            /**
            * Check if the subsequence [i:j[ is empty or as the color `color`
            * @param line The line to test
            * @param i The first index to test
            * @param j The last index to last (! excluded)
            * @param color The color to check (or empty)
            * @return
            */
            bool is_empty_or_match(int line, int i, int j, GridColors color);
            std::vector<std::vector<GridColors>> grid;
        public:
            /**
             * Constructor of the Grid
             * @param n The height
             * @param m The width
             * @param default_color The default color of the grid
             */
            Grid (int n, int m, GridColors default_color = EMPTY);

            /**
            * Check if a line can contain a sequence without considering the current values of the grid
            * @param j The length of the grid
            * @param l The index of the first sequence
            * @param seq The sequence
            * @return
            */
            bool line_can_contain_sequence(int j, int l, std::vector<int> &seq);

            /**
            * Check if a line can contain a sequence, the function is taking under consideration
            * the current values of the line
            * @param line The line to test
            * @param j The first cell of the line to check
            * @param l The first index of the sequence
            * @param seq The sequence
            * @return
            */
            bool line_can_contain_sequence_gen(int line, int j, int l, std::vector<int> &seq);
    };

} // tomographie

#endif //TOMOGRAPHIE_GRID_H
