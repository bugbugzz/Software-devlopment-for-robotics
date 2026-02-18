# Software-devlopment-for-robotics

g++ -Iinclude -c src/MazeSolver.cpp -o src/MazeSolver.o
g++ -Iinclude -c src/main.cpp -o src/main.o
g++ src/MazeSolver.o src/main.o -o assignment2.exe