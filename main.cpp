//=====================...........................=================================
// Authors : Milou de Zwaan (2629070), Shatrunjay Palkar (3669734)
// Group : 14
// License : LGPL open source license
//
// Brief : this program implements a maze solver using a recursive backtracking algorithm. The maze is represented as a 2D grid, where '#' represents walls, '.' represents open paths, and 'x' represents the starting point. The program visualizes the maze-solving process by printing the maze at each step and introducing a delay to show the path being explored. The user can choose to see only the correct path or the entire exploration process by commenting/uncommenting the backtracking line.
//=====================...........................=================================
#include <iostream>
#include <array>
#include <thread> // Required for sleep_for
#include <chrono> // Required for seconds/milliseconds

// Define the dimensions
const size_t ROWS = 12;
const size_t COLS = 12;

// Define a type alias for the maze
using MazeGrid = std::array<std::array<char, COLS>, ROWS>;

// --- NEW: Scoped Enumerator for Direction ---
enum class Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

// --- Function Prototypes ---
void printMaze(const MazeGrid& maze);
bool traverseMaze(MazeGrid& maze, int row, int col, int startRow, int startCol);

int main() {
    // Initialize the maze
    MazeGrid maze = {{
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#'},
        {'.', '.', '#', '.', '#', '.', '#', '#', '#', '#', '.', '#'},
        {'#', '#', '#', '.', '#', '.', '.', '.', '.', '#', '.', '#'},
        {'#', '.', '.', '.', '.', '#', '#', '#', '.', '#', '.', 'x'},
        {'#', '#', '#', '#', '.', '#', '.', '#', '.', '#', '.', '#'},
        {'#', '.', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#'},
        {'#', '#', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#'},
        {'#', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '#'},
        {'#', '#', '#', '#', '#', '#', '.', '#', '#', '#', '.', '#'},
        {'#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
    }};

    int startRow = -1;
    int startCol = -1;

    // 1. Find the starting position 'x'
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            if (maze[r][c] == 'x') {
                startRow = r;
                startCol = c;
            }
        }
    }

    if (startRow != -1) {
        std::cout << "Starting at Row: " << startRow + 1 << ", Col: " << startCol + 1 << std::endl;
        
        maze[startRow][startCol] = '.'; 

        if (traverseMaze(maze, startRow, startCol, startRow, startCol)) {
            std::cout << "\nMAZE SOLVED!" << std::endl;
        } else {
            std::cout << "\nNO EXIT FOUND." << std::endl;
        }
    } else {
        std::cout << "Error: No starting point 'x' found." << std::endl;
    }

    return 0;
}

// --- Function Definitions ---

void printMaze(const MazeGrid& maze) {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif

    for (const auto& row : maze) {
        for (const auto& cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "--------------------------------" << std::endl;
}

// Recursive function to solve the maze
bool traverseMaze(MazeGrid& maze, int row, int col, int startRow, int startCol) {
    
    // 1. Check Bounds (Safety Check)
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        return false;
    }

    // 2. Check if this is a valid move
    if (maze[row][col] != '.') {
        return false;
    }

    // 3. Mark the path
    maze[row][col] = 'x';

    // 4. Visualize the step
    printMaze(maze);
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Adjust the delay as needed

    // 5. Check for Exit
    if (row == 0 || row == ROWS - 1 || col == 0 || col == COLS - 1) {
        if (row != startRow || col != startCol) {
            return true; 
        }
    }

    // 6. Recursive Step: LOOP through all directions
    // Define the order of directions to check
    const Direction directions[] = { Direction::UP, Direction::RIGHT, Direction::DOWN, Direction::LEFT };

    for (const auto& dir : directions) {
        int nextRow = row;
        int nextCol = col;

        // Update coordinates based on the Direction enum
        switch (dir) {
            case Direction::UP:    nextRow--; break;
            case Direction::RIGHT: nextCol++; break;
            case Direction::DOWN:  nextRow++; break;
            case Direction::LEFT:  nextCol--; break;
        }

        // Recursively call for the calculated next cell
        if (traverseMaze(maze, nextRow, nextCol, startRow, startCol)) {
            return true;
        }
    }

    // 7. Backtracking
    maze[row][col] = '.'; // Uncomment to see only correct path
    
    return false;
}