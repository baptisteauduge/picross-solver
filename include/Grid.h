//
// Created by Baptiste Audugé on 04/10/2023.
//

#ifndef TOMOGRAPHIE_GRID_H
#define TOMOGRAPHIE_GRID_H

#include <string>
#include <vector>
#include "utils.h"

#define BLACK_SYMBOL "#"
#define WHITE_SYMBOL " "

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
            * @param line The line to test
            * @param i The first index to test
            * @param j The last index to last (excluded)
            * @param color The color to check (or empty)
            * @return A boolean that indicated if the subsequence [i:j[ is empty or as the provided color at the
             * provided line
            */
            bool is_empty_or_match_line(int line, int i, int j, GridColors color = EMPTY);

            /**
            * @param column The column to test
            * @param i The first index to test
            * @param j The last index to last (excluded)
            * @param color The color to check (or empty)
            * @return A boolean that indicates if the subsequence [i:j[ is empty or as the provided color at the
             * provided column.
            */
            bool is_empty_or_match_col(int col, int i, int j, GridColors color = EMPTY);
            GridSize size;
        public:
            /**
             * Create a new grid of height n and width m
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
            * @return A boolean that indicates if a line can contain a sequence
            */
            bool line_can_contain_sequence(int j, int l, Sequence &seq);

            /**
            * Check if a line can contain a sequence, the function is taking under consideration
            * the current values of the line
            * @param line The line to test
            * @param j The first cell of the line to check
            * @param l The first index of the sequence
            * @param seq The sequence
            * @return A boolean that indicated if a line can contain a sequence
            */
            bool line_can_contain_sequence_gen(int line, int j, int l, Sequence &seq);

            /**
             * Check if a  column can contain a sequence, the function is taking under consideration
             * the current values of the column.
             * @param column The column to test
             * @param j The first cell of the column to check
             * @param l The first index of the sequence
             * @param seq The sequence
             * @return A boolean that indicates if a column can contain a sequence
             */
            bool column_can_contain_sequence_gen(int column, int j, int l, Sequence & seq);

            /**
             * Returns the size of the Grid
             * @return A pair, with as first argument the numerous of line and as second argument the numerous of
             * columns
             */
            GridSize get_size();

            /**
             * Set the cell at [line][col] to the provided value
             * @param line The line to edit
             * @param col The column to edit
             * @param value The new value
             */
            void set_cell(int line, int col, GridColors value);

            /**
             * Returns the current value at [line][col]
             * @param line The line to get the value from
             * @param col The column to get the value from
             * @return Current value at grid[line][col]
             */
            GridColors get_cell(int line, int col);

            /**
             * Print a Grid with as black cell the symbol BLACK_SYMBOL
             * and as white cell the WHITE_SYMBOL.
             * Print a message of error is the Grid is not full (i.e. it contains EMPTY cells)
             */
            void print_grid();
    };
} // tomographie

#endif //TOMOGRAPHIE_GRID_H