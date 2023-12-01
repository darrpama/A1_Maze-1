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

struct Maze {
  Maze(int rows, int cols) : rows(rows), cols(cols) {}
  int rows;
  int cols;
  std::vector<MazeStatement> data;
};

}

#endif  // A1_MAZE_1_0_SRC_MAZE_H
