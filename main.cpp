#include <iostream>
#include <array>
#include <thread> // Required for sleep_for
#include <chrono> // Required for seconds/milliseconds

// Define the dimensions
const size_t ROWS = 12;
const size_t COLS = 12;

// Define a type alias for the maze
using MazeGrid = std::array<std::array<char, COLS>, ROWS>;

// --- Function Prototypes ---
void printMaze(const MazeGrid& maze);
bool traverseMaze(MazeGrid& maze, int row, int col, int startRow, int startCol);

int main() {
    // Initialize the maze
    // '.' = open path, '#' = wall, 'x' = start
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
        
        // Treat the start as a regular cell for the recursive function
        // We temporarily set it to '.' so the function can 'step' on it validly
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
    // System clear command to make the animation look static in place
    // Use "cls" for Windows, "clear" for Linux/Mac
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
    // We can only step on dots '.'
    // If it is a wall '#' or we have already visited it 'x', we stop.
    if (maze[row][col] != '.') {
        return false;
    }

    // 3. Mark the path
    maze[row][col] = 'x';

    // 4. Visualize the step
    printMaze(maze);
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Slow down so user can watch

    // 5. Check for Exit
    // An exit is any spot on the edge of the board that is NOT the start point
    if (row == 0 || row == ROWS - 1 || col == 0 || col == COLS - 1) {
        if (row != startRow || col != startCol) {
            return true; // We found the way out!
        }
    }

    // 6. Recursive Step: Try all 4 directions
    // If ANY of these return true, it means the exit was found down that path.
    
    // Try UP
    if (traverseMaze(maze, row - 1, col, startRow, startCol)) return true;
    
    // Try RIGHT
    if (traverseMaze(maze, row, col + 1, startRow, startCol)) return true;
    
    // Try DOWN
    if (traverseMaze(maze, row + 1, col, startRow, startCol)) return true;
    
    // Try LEFT
    if (traverseMaze(maze, row, col - 1, startRow, startCol)) return true;
    
    maze[row][col] = '.'; // Uncomment this line if you only want to see the Winning Path
    
    return false;
}