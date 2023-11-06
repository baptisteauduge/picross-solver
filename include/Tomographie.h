//
// Created by Baptiste Audugé on 06/11/2023.
//

#ifndef TOMOGRAPHIE_TOMOGRAPHIE_H
#define TOMOGRAPHIE_TOMOGRAPHIE_H

#include "Grid.h"
#include "utils.h"
#include "vector"
#include <set>

namespace tomographie {
    class Tomographie {
    private:
        ListSequence line_seq;
        ListSequence col_seq;
        Grid grid;
        int num_line;
        int num_col;

        /**
         * Returns a set who contains {0, ..., size - 1}
         * @param size The maximum value + 1 in the set
         * @return The resulting set
         */
        static std::set<int> init_range(int size);

        /**
         * Trying coloring curr_line, starting at position curr_col
         * The method will append new_cols_to_see with ì when setting a new cell color on the column i
         * Recursive function
         * @param curr_line Index of the line to treat
         * @param curr_col First index of the column to treat
         * @param new_cols_to_see A set, of columns that has been updated by the method
         * @return A boolean that indicates, if it's possible to fill the line
         */
        bool color_lines_rec(int curr_line, int curr_col, std::set<int> &new_cols_to_see);

        /**
         * Trying coloring curr_col, starting at position curr_line
         * The method will append new_lines_to_see with with ì when setting a new cell color on the line i
         * Recursive function
         * @param curr_line First index of the line to treat
         * @param curr_col Index of the column to treat
         * @param new_lines_to_see A set, of lines that has been updated by the method
         * @return A boolean that indicates, if it's possible to fill the column
         */
        bool color_cols_rec(int curr_line, int curr_col, std::set<int> &new_lines_to_see);
    public:
        /**
         * Create a Tomographie, with line_sequence and col_sequence.
         * Size of the grid is determined considering the size of line_sequence and col_sequence
         * @param line_sequence The list of the sequence that we need to put on the grid, for each line
         * @param col_sequence The list of the sequence that we need to put on the grid, for each column
         */
        Tomographie(ListSequence &line_sequence, ListSequence &col_sequence);

        /**
         * Getter for the Grid
         * @return The Grid contained in the Tomographie
         */
        Grid get_grid();

        /**
         * Method who color the Grid, by taking under consideration the column and line sequences.
         * The method could finish with a Grid that is not full.
         * This is a partial resolution method.
         * @return A boolean that indicates if  it's possible to fill the Grid
         */
        bool color();
    };
}

#endif //TOMOGRAPHIE_TOMOGRAPHIE_H
