#ifndef MAZESOLVER_H
#define MAZESOLVER_H

#include <array>
#include <cstddef> // Required for size_t

class MazeSolver {
public:
    // 1. constants must be static constexpr to define array size
    static constexpr std::size_t ROWS = 12;
    static constexpr std::size_t COLS = 12;

    // 2. Define the type alias using the constants above
    using MazeGrid = std::array<std::array<char, COLS>, ROWS>;

    enum class Direction {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

    // Constructor
    MazeSolver(MazeGrid initialMaze);

    // Public Interface
    void solve();

private:
    MazeGrid maze;
    int startRow;
    int startCol;

    void printMaze() const;
    bool traverse(int row, int col);
};

#endif // MAZESOLVER_H