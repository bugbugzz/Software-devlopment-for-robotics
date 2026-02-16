//=====================...........................=================================
// Authors : Milou de Zwaan (2629070), Shatrunjay Palkar (3669734)
// Group : 14
// License : LGPL open source license
//
// Brief : 
//=====================...........................=================================

#include <iostream>
#include <array>

// Define the dimensions as constants so we can easily change them later
const size_t ROWS = 12; 
const size_t COLS = 12;

// Define a type alias for the maze to make function signatures cleaner, it is a array of arrays of characters, representing the maze grid
using MazeGrid = std::array<std::array<char, COLS>, ROWS>;

// Function to print the maze
void printMaze(const MazeGrid& maze) {
    for (const auto& row : maze) {
        for (const auto& cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << '\n';
    }
}
  
int main() {
    // Initialize the maze as  a 2D array of characters with walls represented by '#' and open paths by '.'x represents the start
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

    // Call the function
    printMaze(maze);

    // for every row iterate over every cell and check if it is the start, if it is print the coordinates of the start
    for (auto& row : maze)
    {
        for (auto& cell : row)
        {   
            if (cell == 'x')
            {
                std::cout << "found the exit at: row " << (&row - &maze[0])+1 << ", col " << (&cell - &row[0])+1 << std::endl;
            }
        }
    }

    return 0;
}

