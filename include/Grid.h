//
// Created by Baptiste Audugé on 04/10/2023.
//

#ifndef TOMOGRAPHIE_GRID_H
#define TOMOGRAPHIE_GRID_H

#include <string>
#include <vector>
#include "utils.h"

namespace tomographie {

    enum GridColors {
        WHITE ,
        BLACK,
        EMPTY
    };

    typedef std::pair<int, int> GridSize;
    typedef std::vector<GridColors> GridLine;

    class Grid {
        private:
            std::vector<GridLine> grid;

            /**
            * Check if the subsequence [i:j[ is empty or as the color `color` at the provided line.
            * @param line The line to test
            * @param i The first index to test
            * @param j The last index to last (! excluded)
            * @param color The color to check (or empty)
            * @return
            */
            bool is_empty_or_match_line(int line, int i, int j, GridColors color);

            /**
            * Check if the subsequence [i:j[ is empty or as the color `color` at the provided column.
            * @param column The column to test
            * @param i The first index to test
            * @param j The last index to last (! excluded)
            * @param color The color to check (or empty)
            * @return
            */
            bool is_empty_or_match_col(int col, int i, int j, GridColors color);

            GridSize size;
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
            bool line_can_contain_sequence(int j, int l, Sequence &seq);

            /**
            * Check if a line can contain a sequence, the function is taking under consideration
            * the current values of the line
            * @param line The line to test
            * @param j The first cell of the line to check
            * @param l The first index of the sequence
            * @param seq The sequence
            * @return
            */
            bool line_can_contain_sequence_gen(int line, int j, int l, Sequence &seq);

            /**
             * Check if a  column can contain a sequence, the function is taking under consideration
             * the current values of the column.
             * @param column The column to test
             * @param j The first cell of the column to check
             * @param l The first index of the sequence
             * @param seq The sequence
             * @return
             */
            bool column_can_contain_sequence_gen(int column, int j, int l, Sequence & seq);

            /**
             * Returns the size of the Grid
             * @return (num_line, num_col)
             */
            GridSize get_size();

            /**
             * Set the cell at [line][col] to the value `value`
             * @param line The line to edit
             * @param col The column to edit
             * @param value The new value
             */
            void set_cell(int line, int col, GridColors value);

            /**
             * Returns the current value at [line][col]
             * @param line The line to get the value from
             * @param col The column to get the value from
             * @return value at grid[line][col]
             */
            GridColors get_cell(int line, int col);

            /**
             * Function used to print a Grid, the function will
             * print a message of error is the Grid is not full
             * i.e. it contains EMPTY cells
             */
            void print_grid();
    };

} // tomographie

#endif //TOMOGRAPHIE_GRID_H
