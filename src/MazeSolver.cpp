//=====================...........................=================================
// Authors : Milou de Zwaan (2629070), Shatrunjay Palkar (3669734)
// Group : 14
// License : LGPL open source license
//
// Brief : Implementation of the recursive maze solver. it contains the logic to traverse the maze, print the current state of the maze, and determine if the exit has been found.
//=====================...........................=================================

#include "MazeSolver.h" // Include the MazeSolver header to implement the class methods
#include <iostream> // Required for input/output operations
#include <thread> // Required for std::this_thread::sleep_for
#include <chrono> // Required for std::chrono::milliseconds

// Constructor
MazeSolver::MazeSolver(MazeSolver::MazeGrid initialMaze) 
    : maze(initialMaze), startRow(-1), startCol(-1) {
    
    // Find the starting position 'x' in the maze by iterating through the grid
    for (int r = 0; r < static_cast<int>(ROWS); ++r) {
        for (int c = 0; c < static_cast<int>(COLS); ++c) {
            if (maze[r][c] == 'x') {
                startRow = r;
                startCol = c;
            }
        }
    }
}

// Public method to start solving the maze, by calling the private traverse method
void MazeSolver::solve() {
    if (startRow != -1) { // Check if a starting point was found
        std::cout << "Starting at Row: " << startRow + 1 << ", Col: " << startCol + 1 << std::endl;
        maze[startRow][startCol] = '.'; 
        if (traverse(startRow, startCol)) { // If traverse returns true, the maze is solved
            std::cout << "\nMAZE SOLVED!" << std::endl;
        } else {
            std::cout << "\nNO EXIT FOUND." << std::endl;
        }
    } else {
        std::cout << "Error: No starting point 'x' found." << std::endl;
    }
}

// Private method to print the current state of the maze to the console, to visualize the traversal process. It clears the console before printing the maze.
void MazeSolver::printMaze() const {
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

// Private method to traverse the maze recursively. it checks for valid moves, marks the path.
bool MazeSolver::traverse(int row, int col) {
    // Check Bounds
    if (row < 0 || row >= static_cast<int>(ROWS) || col < 0 || col >= static_cast<int>(COLS) || maze[row][col] != '.') {
        return false;
    }

    // Mark the current cell as part of the path
    maze[row][col] = 'x';
    printMaze();
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Pause for 500 milliseconds to visualize the traversal

    // Check Exit
    if (row == 0 || row == static_cast<int>(ROWS) - 1 || col == 0 || col == static_cast<int>(COLS) - 1) {
        if (row != startRow || col != startCol) {
            return true; 
        }
    }

    // Define the possible directions to move (up, right, down, left)
    const Direction directions[] = { Direction::UP, Direction::RIGHT, Direction::DOWN, Direction::LEFT }; 

    // Recursive Step: Loop through all 4 directions
    for (const auto& dir : directions) {
        int nextRow = row;
        int nextCol = col;

        // Update coordinates based on direction
        switch (dir) {
            case Direction::UP:    nextRow--; break;
            case Direction::RIGHT: nextCol++; break;
            case Direction::DOWN:  nextRow++; break;
            case Direction::LEFT:  nextCol--; break;
        }

        // attempt to solve the maze starting from the 'next' cell.
        // If traverse() returns true, it means the exit was found down that path.
        // Immediately return true to signal the success along the chain of function calls.
         // If traverse() returns false, it means that direction was a dead end.
        // The loop continues automatically to try the next direction.
        if (traverse(nextRow, nextCol)) {
            return true;
        }
    }
    
    return false; // Signal to the previous caller that this path failed.
}