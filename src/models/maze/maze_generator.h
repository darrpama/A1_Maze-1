#ifndef MAZE_GEN_H
#define MAZE_GEN_H

#include <algorithm>
#include <random>
#include <unordered_map>
#include <vector>

#include "maze.h"

namespace s21 {

class MazeGenerator {
 public:
  const int kEmptyCell = -1;

  MazeGenerator();
  Maze GenerateMaze(int rows, int cols, float right_wall_chance = 0.5,
                    float bottom_wall_chance = 0.5);

 private:
  size_t next_set_;
  std::unordered_map<size_t, std::vector<size_t>> sets_;
  std::vector<int> cells_;

  void FillEmptyCells(int cols);
  void AddRightWalls(Maze& maze, int row, float right_wall_chance);
  void AddBottomWalls(Maze& maze, int row, float bottom_wall_chance);
  void AddEndLine(Maze& maze, float right_wall_chance);

  bool RandomChoice(float chance);
  void MergeSets(size_t set1, size_t set2);
  void Clear();
};

}  // namespace s21

#endif  // A1_MAZE_1_0_SRC_MAZE_GENERATOR_H
