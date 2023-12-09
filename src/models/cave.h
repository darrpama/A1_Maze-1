#ifndef A1_MAZE_1_0_SRC_MODEL_CAVE_H
#define A1_MAZE_1_0_SRC_MODEL_CAVE_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#include "../type.h"

namespace s21 {

class Cave {
 public:
  Cave(int rows, int cols) : rows_(rows), cols_(cols), matrix_{} {}

  int GetRows();
  int GetCols();
  void SetRows(int);
  void SetCols(int);
  void Push(unsigned);
  std::vector<unsigned>& GetMatrix();

  void Clear();

 private:
  int rows_;
  int cols_;
  std::vector<unsigned> matrix_;
};

}  // namespace s21

#endif  // A1_MAZE_1_0_SRC_MODEL_CAVE_H
