#ifndef A1_MAZE_1_0_SRC_MAZE_H
#define A1_MAZE_1_0_SRC_MAZE_H

#include <iostream>
#include <vector>

namespace s21 {

enum Border {
  NO_BORDER = 0,
  RIGHT_BORDER,
  BOTTOM_BORDER,
  BOTH_BORDER,
};

class Maze {
 public:
  Maze(int rows, int cols) : rows_(rows), cols_(cols), matrix_{} {}

  void Clear();
  int GetRows();
  int GetCols();
  void SetRows(int);
  void SetCols(int);
  void Push(Border);
  std::vector<Border>& GetMatrix();

 private:
  int rows_;
  int cols_;
  std::vector<Border> matrix_;
};

}  // namespace s21

#endif  // A1_MAZE_1_0_SRC_MAZE_H
