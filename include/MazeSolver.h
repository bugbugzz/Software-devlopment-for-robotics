//=====================...........................=================================
// Authors : Milou de Zwaan (2629070), Shatrunjay Palkar (3669734)
// Group : 14
// License : LGPL open source license
//
// Brief : contains the declaration of the MazeSolver class, which implements a recursive maze solver.
//=====================...........................=================================

#ifndef MAZESOLVER_H // Include guard to prevent multiple inclusions
#define MAZESOLVER_H // Include necessary headers

#include <array> // Required for std::array
#include <cstddef> // Required for size_t

class MazeSolver {
public:
    // constants must be static constexpr to define array size
    static constexpr std::size_t ROWS = 12;
    static constexpr std::size_t COLS = 12;

    // Define the type alias using the constants above
    using MazeGrid = std::array<std::array<char, COLS>, ROWS>;

    enum class Direction {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

    // Constructor
    MazeSolver(MazeGrid initialMaze);

    // Public method to start solving the maze
    void solve();

private:
    // Maze grid and starting position
    MazeGrid maze;
    int startRow;
    int startCol;

    // Private helper methods
    void printMaze() const;
    bool traverse(int row, int col);
};

#endif // MAZESOLVER_H