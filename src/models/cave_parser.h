#ifndef A1_MAZE_1_0_SRC_CAVE_PARSER_H
#define A1_MAZE_1_0_SRC_CAVE_PARSER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "cave.h"

namespace s21 {

class CaveParser {
 public:
  explicit CaveParser(Cave *cave) : cave_(cave){};
  void Parse();
  void SetFilePath(const std::string &);

 private:
  Cave *cave_;
  std::string filepath_;
  std::vector<unsigned> matrix_;
  int current_line_ = 0;

  void CheckAndFixEndLine();
  void ParseSize(std::string &);
  void ParseMatrix(std::string &);
  void Reset();
};

}  // namespace s21

#endif  // A1_MAZE_1_0_SRC_CAVE_PARSER_H
