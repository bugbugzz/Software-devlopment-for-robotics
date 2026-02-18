//=====================...........................=================================
// Authors : Milou de Zwaan (2629070), Shatrunjay Palkar (3669734)
// Group : 14
// License : LGPL open source license
//
// Brief : contains the declaration of the MazeSolver class, which implements a maze solver using a recursive backtracking algorithm. The maze is represented as a 2D grid, where '#' represents walls, '.' represents open paths, and 'x' represents the starting point. The class provides methods to visualize the maze-solving process and to find the exit from the maze.
//=====================...........................=================================
#ifndef MAZESOLVER_H
#define MAZESOLVER_H

#include <array>

class MazeSolver {
public:
    // --- Constants and Type Aliases ---
    // Moved from global constants in main.cpp
    static const size_t ROWS = 12;
    static const size_t COLS = 12;

    // Define the maze grid type alias
    using MazeGrid = std::array<std::array<char, COLS>, ROWS>;

    // --- Scoped Enumerator for Direction ---
    // Kept as an enum class for strong typing
    enum class Direction {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

    // --- Constructor ---
    /*
     @brief Initializes the solver with a grid.
     @param initialMaze The 2D grid representing the maze.
     */
    MazeSolver(MazeGrid initialMaze);

    // --- Public Interface ---
    void solve();

private:
    // --- Member Variables ---
    // Encapsulated data accessible to all class methods
    MazeGrid maze;
    int startRow;
    int startCol;

    // --- Private Helper Methods (Function Prototypes) ---
    void printMaze() const;

    // Recursive function to solve the maze
    bool traverse(int row, int col);
};

#endif // MAZESOLVER_H