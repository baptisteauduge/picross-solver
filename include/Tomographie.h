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
         * Trying to color curr_line, starting at position curr_col of curr_grid
         * The method will append new_cols_to_see with i when setting a new cell color on the column i
         * Recursive function
         * @param curr_line Index of the line to treat
         * @param curr_col First index of the column to treat
         * @param new_cols_to_see A set, of columns that has been updated by the method
         * @param curr_grid The current Grid to color
         * @return A boolean that indicates, if it's possible to fill the line
         */
        bool color_lines_rec(int curr_line, int curr_col, std::set<int> &new_cols_to_see, Grid &curr_grid);

        /**
         * Trying to color curr_line, starting at position curr_col of the grid instance variable
         * The method will append new_cols_to_see with ì when setting a new cell color on the column i
         * Recursive function
         * @param curr_line Index of the line to treat
         * @param curr_col First index of the column to treat
         * @param new_cols_to_see A set, of columns that has been updated by the method
         * @return A boolean that indicates, if it's possible to fill the line
         */
        bool color_lines_rec(int curr_line, int curr_col, std::set<int> &new_cols_to_see);

        /**
         * Trying to color curr_col, starting at position curr_line of curr_grid
         * The method will append new_lines_to_see with with ì when setting a new cell color on the line i
         * Recursive function
         * @param curr_line First index of the line to treat
         * @param curr_col Index of the column to treat
         * @param new_lines_to_see A set, of lines that has been updated by the method
         * @param curr_grid The current Grid to color.
         * @return A boolean that indicates, if it's possible to fill the column
         */
        bool color_cols_rec(int curr_line, int curr_col, std::set<int> &new_lines_to_see, Grid &curr_grid);

        /**
         * Trying to color curr_col, starting at position curr_line of the instance variable grid
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
         * @return A TriState that indicates if it's possible to fill the Grid
         */
        TriState color();

        /**
         * Method used to fully complete the grid, it will enumerate all possibilities recursively
         * @return A boolean that indicates if the grid as a solution, if the Grid as a Solution,
         * it will be set into the instance variable grid.
         */
        bool enumeration();

        /**
         * Recursive function that will enumerate all possibilities to fill the a Grid, that may be not empty at the
         * the begging.
         * @param grid The grid that we will try to fill
         * @param k The first cell index to fill (if cell (i, j) will be i*M + j)
         * @param c The color we will try to put in the cell k
         * @return A pair, with a boolean that indicates if it's possible to fill the Grid or not, and the resulting
         * Grid if possible, or an Empty Grid if not
         */
        std::pair<bool, Grid> enumeration_rec(Grid &curr_grid, int k, CellColor c);

        /**
         * Function used to color and propagate, the cell i, j to the Color C
         * @param curr_grid The Grid to color
         * @param i The line index
         * @param j The column index
         * @param c The color to put at cell (i, j)
         * @return A boolean that indicates if the grid has been filled
         */
        TriState color_propagate(Grid &curr_grid, int i, int j, CellColor c);
    };
}

#endif //TOMOGRAPHIE_TOMOGRAPHIE_H
