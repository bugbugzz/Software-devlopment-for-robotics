#include "MazeSolver.h"
#include <iostream>
#include <thread>
#include <chrono>

// Constructor
MazeSolver::MazeSolver(MazeSolver::MazeGrid initialMaze) 
    : maze(initialMaze), startRow(-1), startCol(-1) {
    
    // Cast static constants to int for the loop
    for (int r = 0; r < static_cast<int>(ROWS); ++r) {
        for (int c = 0; c < static_cast<int>(COLS); ++c) {
            if (maze[r][c] == 'x') {
                startRow = r;
                startCol = c;
            }
        }
    }
}

void MazeSolver::solve() {
    if (startRow != -1) {
        std::cout << "Starting at Row: " << startRow + 1 << ", Col: " << startCol + 1 << std::endl;
        
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

bool MazeSolver::traverse(int row, int col) {
    // Check Bounds
    if (row < 0 || row >= static_cast<int>(ROWS) || col < 0 || col >= static_cast<int>(COLS) || maze[row][col] != '.') {
        return false;
    }

    maze[row][col] = 'x';
    printMaze();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Check Exit
    if (row == 0 || row == static_cast<int>(ROWS) - 1 || col == 0 || col == static_cast<int>(COLS) - 1) {
        if (row != startRow || col != startCol) {
            return true; 
        }
    }

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

    maze[row][col] = '.'; 
    return false;
}