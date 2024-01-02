#ifndef A1_MAZE_1_0_SRC_MAZE_H
#define A1_MAZE_1_0_SRC_MAZE_H

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#include "../type.h"

namespace s21 {

class Maze {
 public:
  Maze(int rows, int cols) : rows_(rows), cols_(cols), matrix_{} {}

  int GetRows();
  int GetCols();
  void SetRows(int);
  void SetCols(int);
  void Push(Border);
  std::vector<Border>& GetMatrix();
  void Clear();
  bool CheckBorder(int, int, int, int, int, int, int);
  bool IsIdeal();
  std::vector<Vector2D> Resolve(Vector2D, Vector2D);

 private:
  int rows_ = 0;
  int cols_ = 0;
  std::vector<Border> matrix_;

  std::vector<int> FindPath(Vector2D, Vector2D);
  std::vector<Vector2D> FindSolution(Vector2D, Vector2D, const std::vector<int>&);
};

}  // namespace s21

#endif  // A1_MAZE_1_0_SRC_MAZE_H
