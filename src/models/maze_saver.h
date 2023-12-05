#ifndef A1_MAZE_1_0_SRC_MAZE_SAVER_H
#define A1_MAZE_1_0_SRC_MAZE_SAVER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "maze.h"

namespace s21 {

class MazeSaver {
 public:
  explicit MazeSaver(const Maze &maze) : maze_(&maze){};
  void Save();
  void SetFilePath(const std::string &);

 private:
  Maze *maze_;
  std::string filepath_;
  std::vector<Border> right_matrix_;
  std::vector<Border> bottom_matrix_;
};

}  // namespace s21

#endif  // A1_MAZE_1_0_SRC_MAZE_SAVER_H
