#ifndef A1_MAZE_1_0_SRC_MAZE_H
#define A1_MAZE_1_0_SRC_MAZE_H

#include <iostream>
#include <vector>

namespace s21 {

enum MazeStatement {
  NO_BORDER = 0,
  RIGHT_BORDER,
  BOTTOM_BORDER,
  BOTH_BORDER,
};

class Maze {
 public:
  Maze(int rows, int cols) : rows_(rows), cols_(cols) {}

  void Clear();
  int GetRows();
  int GetCols();
  void SetRows(int);
  void SetCols(int);
  void SetMazeStatement(std::vector<MazeStatement> &);
  std::vector<MazeStatement> GetMazeStatement();

 private:
  int rows_;
  int cols_;
  std::vector<MazeStatement> *maze_statement_;
};

}

#endif  // A1_MAZE_1_0_SRC_MAZE_H
