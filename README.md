# Picross Solver

This project is a solver for the game [Picross](https://en.wikipedia.org/wiki/Nonogram) (also known as Nonogram). The solver is implemented in C++ using dynamic programming and backtracking (forward checking) algorithms.

## Implementation

The solver is implemented in the `tomographie` namespace, and the solver class is `Tomographie`. The `Tomographie` class has two main methods: `color` and `enumeration`. The `color` method uses dynamic programming to solve the puzzle, and the `enumeration` method uses backtracking to solve the puzzle.

The `color` method is the fastest method, and it is the default method used by the solver. The `enumeration` method is slower, but it is guaranteed to find a solution if one exists.

The `enumeration` method is also using the `color` method to solve the puzzle, but it is using backtracking to explore all possible solutions.

In other words, you can always use the `enumeration` method, that will find a solution in a really short time if propagation is enough, and if not, it will use an exhaustive search to find a solution.

## Usage

The solver comes with a command line interface. You can use the solver by running the `tomographie` executable and passing the puzzle file as an argument.

The puzzle file is a text file with the following format:

```
3
1 1 1
3
1 1
1 1
#
1 1
1 2
3
1 2
1 1
```

Where the each line until the `#` is a row, and each line after the `#` is a column.

```
./tomographie <-p|-c> puzzle.txt
```
  
  Where `-p` is the method to use (partial or complete (for `-c`)) and `puzzle.txt` is the puzzle file.

## Example

You can run the following command to solve the puzzle in the file `tests/input/0.txt`:

```
./tomographie -p tests/input/0.txt
```

The output will be:

```
Opening file "../tests/input/0.txt" ...
File opened!
Time taken by program is : 0.000244708 sec 
Is grid successfully filled : 1
■■■□□
□□□□□
■□■□■
□□■■■
```
