#ifndef MAZE_GEN_H
#define MAZE_GEN_H

#include <algorithm>
#include <vector>
#include <random>
#include <unordered_map>
#include "maze.h"

namespace s21 {
    class MazeGenerator {
       public:
        const int kEmptyCell = -1;

        MazeGenerator();
        Maze generateMaze(int rows, int cols, float right_wall_chance = 0.5, float bottom_wall_chance = 0.5);
       
       private:
        void FillEmptyCells(int cols);
        void AddRightWalls(Maze& maze, int row, float right_wall_chance);
        void AddBottomWalls(Maze& maze, int row, float bottom_wall_chance);
        void AddEndLine(Maze& maze, float right_wall_chance);

        bool RandomChoice(float chance);
        void MergeSets(size_t set1, size_t set2);
        void Clear();

        size_t next_set;
        std::unordered_map<size_t, std::vector<size_t>> sets;
        std::vector<int> cells;
    };
}

#endif
