#ifndef A1_MAZE_1_0_SRC_MAZE_PARSER_H
#define A1_MAZE_1_0_SRC_MAZE_PARSER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "maze.h"

namespace s21 {

class MazeParser {
  public:
    explicit MazeParser(Maze *maze) : maze_(maze) {};
    void Parse();
    void SetFilePath(const std::string &);
  
  private:
    Maze *maze_;
    std::string filepath_;
    std::vector<MazeStatement> maze_state_;

    void ParseSize(std::string &);
    void ParseMatrixRight(std::string &);
    void ParseMatrixBottom(std::string &);
};

}

#endif  // A1_MAZE_1_0_SRC_MAZE_PARSER_H
