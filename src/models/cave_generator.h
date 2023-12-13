#ifndef A1_MAZE_1_SRC_MODELS_CAVE_GENERATOR_H
#define A1_MAZE_1_SRC_MODELS_CAVE_GENERATOR_H

#include <algorithm>
#include <vector>
#include <random>
#include <unordered_map>
#include "cave.h"

namespace s21 {
class CaveGenerator {
 public:
  CaveGenerator();
  Cave Generate(size_t rows, size_t cols, float chance);
  bool Step(Cave *cave, unsigned die_limit, unsigned born_limit);
  
 private:
  unsigned rows_;
  unsigned cols_;
  std::vector<unsigned> cells_;

  bool CompareCaves(Cave *old_cave, Cave *new_cave);
  bool RandomChoice(float chance);
  size_t GetAliveNeigborsCount(Cave *cave, size_t row, size_t col);
  size_t GetNorthWest(Cave *cave, size_t row, size_t col);
  size_t GetNorth(Cave *cave, size_t row, size_t col);
  size_t GetNorthEast(Cave *cave, size_t row, size_t col);
  size_t GetEast(Cave *cave, size_t row, size_t col);
  size_t GetSouthEast(Cave *cave, size_t row, size_t col);
  size_t GetSouth(Cave *cave, size_t row, size_t col);
  size_t GetSouthWest(Cave *cave, size_t row, size_t col);
  size_t GetWest(Cave *cave, size_t row, size_t col);
  void Clear();
};
}  // namespace s21

#endif  // A1_MAZE_1_SRC_MODELS_CAVE_GENERATOR_H
