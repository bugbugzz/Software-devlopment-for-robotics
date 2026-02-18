# Software-devlopment-for-robotics
NORMAL:
compile:
g++ -Iinclude -c src/MazeSolver.cpp -o src/MazeSolver.o
g++ -Iinclude -c src/main.cpp -o src/main.o
build:
g++ src/MazeSolver.o src/main.o -o assignment2.exe

run:./assignment2


TEST:
compile:
g++ -Iinclude -c src/MazeSolver.cpp -o src/MazeSolver.o
g++ -Iinclude -c src/test.cpp -o src/test.o
build:
g++ src/MazeSolver.o src/test.o -o test.exe

run:./test