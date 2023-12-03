#ifndef MAZE_GEN_H
#define MAZE_GEN_H

#include <csignal>

#include <algorithm>
#include <vector>
#include <random>
#include <unordered_map>
#include "../Maze/maze.h"

namespace s21 {
    class MazeGenerator {
       public:
        const int kEmptyCell = -1;

        MazeGenerator();
        Maze generateMaze(int rows, int cols);
       
       private:
        void FillEmptyCells(int cols);
        void AddRightWalls(Maze& maze, int row);
        void AddBottomWalls(Maze& maze, int row);
        void AddEndLine(Maze& maze);

        bool randomChoice();
        void mergeSets(size_t set1, size_t set2);

        size_t next_set;
        std::unordered_map<size_t, std::vector<size_t>> sets;
        std::vector<int> cells;
    };
}

#endif
