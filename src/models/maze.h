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
  std::vector<int> FindPath(std::pair<size_t, size_t>,
                            std::pair<size_t, size_t>);
  std::vector<std::pair<size_t, size_t>> FindSolution(std::pair<size_t, size_t>,
                                                      std::pair<size_t, size_t>,
                                                      const std::vector<int>&);
  std::vector<std::pair<size_t, size_t>> Resolve(std::pair<size_t, size_t>,
                                                 std::pair<size_t, size_t>);

 private:
  int rows_;
  int cols_;
  std::vector<Border> matrix_;
};

}  // namespace s21

#endif  // A1_MAZE_1_0_SRC_MAZE_H
