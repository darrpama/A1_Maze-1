#ifndef A1_MAZE_1_0_SRC_MAZE_PARSER_H
#define A1_MAZE_1_0_SRC_MAZE_PARSER_H

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
