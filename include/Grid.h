//
// Created by Baptiste Audugé on 04/10/2023.
//

#ifndef TOMOGRAPHIE_GRID_H
#define TOMOGRAPHIE_GRID_H

#include <string>
#include <vector>
#include <map>
#include "utils.h"

#define BLACK_SYMBOL "◼︎"
#define WHITE_SYMBOL "・"

namespace tomographie {

    enum class CellColor {
        WHITE ,
        BLACK,
        EMPTY
    };

    typedef std::pair<int, int> GridSize;
    typedef std::vector<CellColor> GridLine;
    typedef std::map<std::tuple<int, int>, bool> CacheCanContain;

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
            bool is_empty_or_match_line(int line, int i, int j, CellColor color = CellColor::EMPTY);

            /**
            * @param column The column to test
            * @param i The first index to test
            * @param j The last index to last (excluded)
            * @param color The color to check (or empty)
            * @return A boolean that indicates if the subsequence [i:j[ is empty or as the provided color at the
             * provided column.
            */
            bool is_empty_or_match_col(int col, int i, int j, CellColor color = CellColor::EMPTY);

            /**
            * Check if a line can contain a sequence, the function is taking under consideration
            * the current values of the line
            * @param line The line to test
            * @param j The first cell of the line to check
            * @param l The first index of the sequence
            * @param seq The sequence
            * @return A boolean that indicated if a line can contain a sequence
            */
            bool column_can_contain_sequence_gen(int column, int j, int l, Sequence & seq);

            /**
            * Check if a  column can contain a sequence, the function is taking under consideration
            * the current values of the column.
            * @param column The column to test
            * @param j The first cell of the column to check
            * @param l The first index of the sequence
            * @param seq The sequence
            * @return A boolean that indicates if a column can contain a sequence
            */
            bool line_can_contain_sequence_gen(int line, int j, int l, Sequence &seq);

            /**
             * Cache used by method column can contain sequence, in way to make dynamic programming
             */
            CacheCanContain cache_contain_col = CacheCanContain();

            /**
             * Cache used by method line can contain sequence, in way to make dynamic programming
             */
            CacheCanContain cache_contain_line = CacheCanContain();

            /**
             * The size of the grid ...
             */
            GridSize size;
        public:
            /**
             * Create a new grid of height n and width m
             * @param n The height
             * @param m The width
             * @param default_color The default color of the grid
             */
            Grid (int n, int m, CellColor default_color = CellColor::EMPTY);

            /**
             * A copy constructor
             * @param other Another Grid to copy
             */
            Grid (const Grid &other);

            /**
             * Creates an empty grid
             */
            Grid ();

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
            * The function will use dynamic programming to have a O(n^3) complexity.
            * @param line The line to test
            * @param j The first cell of the line to check
            * @param l The first index of the sequence
            * @param seq The sequence
            * @return A boolean that indicated if a line can contain a sequence
            */
            bool line_can_contain_sequence_cache(int line, int j, int l, Sequence &seq, bool reset_cache = true);


            /**
            * Check if a  column can contain a sequence, the function is taking under consideration
            * the current values of the column.
            * The function will use dynamic programming to have a O(n^3) complexity
            * @param column The column to test
            * @param j The first cell of the column to check
            * @param l The first index of the sequence
            * @param seq The sequence
            * @return A boolean that indicates if a column can contain a sequence
            */
            bool column_can_contain_sequence_cache(int column, int j, int l, Sequence & seq, bool reset_cache = true);

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
            void set_cell(int line, int col, CellColor value);

            /**
             * Returns the current value at [line][col]
             * @param line The line to get the value from
             * @param col The column to get the value from
             * @return Current value at grid[line][col]
             */
            CellColor get_cell(int line, int col);

            /**
             * Print a Grid with as black cell the symbol BLACK_SYMBOL
             * and as white cell the WHITE_SYMBOL.
             * Print a message of error is the Grid is not full (i.e. it contains EMPTY cells)
             */
            void print_grid();

            /**
             * Static method that returns an empty Grid
             * @return
             */
            static Grid get_empty_grid();

            /**
             * Returns true if the Grid doesn't have an EMPTY cell, false otherwise
             * @return A boolean that indicates if the Grid is full or not
             */
            bool is_full();
    };
} // tomographie

#endif //TOMOGRAPHIE_GRID_H
