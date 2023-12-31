#ifndef A1_MAZE_1_0_SRC_MAZE_PARSER_H
#define A1_MAZE_1_0_SRC_MAZE_PARSER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "maze.h"

namespace s21 {

class MazeParser {
 public:
  explicit MazeParser(Maze *maze) : maze_(maze){};
  void Parse();
  void SetFilePath(const std::string &);

 private:
  Maze *maze_;
  std::string filepath_;
  std::vector<Border> right_matrix_;
  std::vector<Border> bottom_matrix_;
  int current_line_ = 0;

  void CheckAndFixEndLine();
  void ParseSize(const std::string &);
  void ParseMatrixRight(const std::string &);
  void ParseMatrixBottom(const std::string &);
  void MergeMatricies();
  void Reset();
};

}  // namespace s21

#endif  // A1_MAZE_1_0_SRC_MAZE_PARSER_H
