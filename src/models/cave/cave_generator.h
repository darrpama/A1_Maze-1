#ifndef A1_MAZE_1_SRC_MODELS_CAVE_GENERATOR_H
#define A1_MAZE_1_SRC_MODELS_CAVE_GENERATOR_H

#include <algorithm>
#include <random>
#include <unordered_map>
#include <vector>

#include "cave.h"

namespace s21 {

class CaveGenerator {
 public:
  CaveGenerator();
  Cave Generate(size_t rows, size_t cols, float chance);
  bool Step(Cave *cave, unsigned die_limit, unsigned born_limit);
  
 private:
  std::vector<unsigned> cells_;
  int rows_;
  int cols_;
  int current_row_;
  int current_col_;

  bool CompareCaves(Cave *old_cave, Cave *new_cave);
  bool RandomChoice(float chance);
  int GetAliveNeigborsCount(Cave *cave);
  int GetNorthWest(Cave *cave);
  int GetNorth(Cave *cave);
  int GetNorthEast(Cave *cave);
  int GetEast(Cave *cave);
  int GetSouthEast(Cave *cave);
  int GetSouth(Cave *cave);
  int GetSouthWest(Cave *cave);
  int GetWest(Cave *cave);
  void Clear();
};

}  // namespace s21

#endif  // A1_MAZE_1_SRC_MODELS_CAVE_GENERATOR_H
