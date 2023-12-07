#ifndef A1_MAZE_1_SRC_MODELS_MODEL_H
#define A1_MAZE_1_SRC_MODELS_MODEL_H

#include "maze.h"
#include "../type.h"

namespace s21 {

class Model {
 public:
  Model(Maze *m, MazeParser *mp) : maze_(m), maze_parser_(mp) {};
  void UploadMaze(std::string);

 private:
  Maze *maze_;
  MazeParser *maze_parser_;
};

}  // namespace s21

#endif  // A1_MAZE_1_SRC_MODELS_MODEL_H
