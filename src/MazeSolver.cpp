//=============================================================================
// Authors : Milou de Zwaan (2629070), Shatrunjay Palkar (3669734)
// Group : 14
// License : LGPL open source license
// Brief : Implementation of the recursive maze solver logic.
//=============================================================================

#include "MazeSolver.h"
#include <iostream>
#include <thread>
#include <chrono>

// --- CONSTRUCTOR ---
MazeSolver::MazeSolver(MazeSolver::MazeGrid initialMaze) 
    : maze(initialMaze), startRow(-1), startCol(-1) {
    
    // Scan the grid to locate the starting point 'x'
    for (int r = 0; r < static_cast<int>(ROWS); ++r) {
        for (int c = 0; c < static_cast<int>(COLS); ++c) {
            if (maze[r][c] == 'x') {
                startRow = r;
                startCol = c;
            }
        }
    }
}

// --- PUBLIC SOLVE METHOD ---
void MazeSolver::solve() {
    if (startRow != -1) {
        std::cout << "Starting at Row: " << startRow + 1 << ", Col: " << startCol + 1 << std::endl;
        
        // Clear the start position so it can be traversed
        maze[startRow][startCol] = '.'; 

        if (traverse(startRow, startCol)) {
            std::cout << "\nMAZE SOLVED!" << std::endl;
        } else {
            std::cout << "\nNO EXIT FOUND." << std::endl;
        }
    } else {
        std::cout << "Error: No starting point 'x' found." << std::endl;
    }
}

// --- VISUALIZATION HELPER ---
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

// --- RECURSIVE TRAVERSAL LOGIC ---
bool MazeSolver::traverse(int row, int col) {
    /* ---------------------------------------------------------
       1. Boundary check    
       Check if we are out of bounds or hitting a wall/visited cell.
       --------------------------------------------------------- */
    if (row < 0 || row >= static_cast<int>(ROWS) || 
        col < 0 || col >= static_cast<int>(COLS) || 
        maze[row][col] != '.') {
        return false;
    }

    /* ---------------------------------------------------------
       2. mark and print
       Mark this cell as 'visited' (x) and show it on screen.
       --------------------------------------------------------- */
    maze[row][col] = 'x';
    printMaze();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    /* ---------------------------------------------------------
       3. Check for exit
       If we reached the border (and it's not the start), we win.
       --------------------------------------------------------- */
    if (row == 0 || row == static_cast<int>(ROWS) - 1 || 
        col == 0 || col == static_cast<int>(COLS) - 1) {
        if (row != startRow || col != startCol) {
            return true; 
        }
    }

    /* ---------------------------------------------------------
       4. recursive exploration
       Try moving in all 4 directions. If a path returns true,
       we propagate that success up the call stack.
       --------------------------------------------------------- */
    const Direction directions[] = { Direction::UP, Direction::RIGHT, Direction::DOWN, Direction::LEFT };

    for (const auto& dir : directions) {
        int nextRow = row;
        int nextCol = col;

        switch (dir) {
            case Direction::UP:    nextRow--; break;
            case Direction::RIGHT: nextCol++; break;
            case Direction::DOWN:  nextRow++; break;
            case Direction::LEFT:  nextCol--; break;
        }

        if (traverse(nextRow, nextCol)) {
            return true;
        }
    }

    /* ---------------------------------------------------------
       5. DEAD END
       If loop finishes, no exit was found from here.
       Note: We leave 'x' marked to show this area was visited.
       --------------------------------------------------------- */
    return false;
}