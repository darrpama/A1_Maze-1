#ifndef A1_MAZE_1_0_SRC_MAZE_PARSER_H
#define A1_MAZE_1_0_SRC_MAZE_PARSER_H

#include <iostream>
#include <vector>

#include "maze.h"

namespace s21 {

class MazeParser {
  public:
    void Parse();
    void SetFilePath(const std::string &);
  
  private:
    Maze *maze_;
    void ParseSize(std::string &);
    void ParseMatrixRight(std::string &);
    void ParseMatrixBottom(std::string &);
};

}

#endif  // A1_MAZE_1_0_SRC_MAZE_PARSER_H
