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
  
 private:
  std::vector<unsigned> cells_;

  void AddCell(Cave& cave, size_t row, float chance);
  bool RandomChoice(float chance);
  void Clear();
};
}  // namespace s21

#endif  // A1_MAZE_1_SRC_MODELS_CAVE_GENERATOR_H
