//=============================================================================
// Authors : Milou de Zwaan (2629070), Shatrunjay Palkar (3669734)
// Group : 14
// License : LGPL open source license
// Brief : Declaration of the MazeSolver class for recursive maze solving.
//=============================================================================

#ifndef MAZESOLVER_H
#define MAZESOLVER_H

#include <array>
#include <cstddef> // Required for size_t

class MazeSolver {
public:
    // --- CONSTANTS ---
    // Static constexpr ensures these are known at compile time for array sizing
    static constexpr std::size_t ROWS = 12;
    static constexpr std::size_t COLS = 12;

    // --- TYPES ---
    // Alias for the 2D grid structure,aliasing a 2D array of chars for better readability
    using MazeGrid = std::array<std::array<char, COLS>, ROWS>;

    // Scoped enum for navigation directions
    enum class Direction {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

    // --- CONSTRUCTOR ---
    /**
     * @brief Initializes the solver with a given maze.
     * @param initialMaze The grid containing walls, paths, and start point.
     */
    MazeSolver(MazeGrid initialMaze);

    // --- PUBLIC METHODS ---
    /**
     * @brief Starts the maze solving process.
     */
    void solve();

private:
    // --- MEMBER VARIABLES ---
    MazeGrid maze; // The 2D grid representing the current state of the maze
    int startRow;  // Cached row index of the starting position 'x'
    int startCol;  // Cached column index of the starting position 'x'

    // --- HELPER METHODS ---
    void printMaze() const;
    bool traverseMaze(int row, int col);
};

#endif // MAZESOLVER_H
