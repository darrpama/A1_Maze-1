#ifndef A1_MAZE_1_SRC_MODELS_MODEL_H
#define A1_MAZE_1_SRC_MODELS_MODEL_H

#include "maze.h"
#include "maze_parser.h"
#include "maze_generator.h"
#include "../type.h"

namespace s21 {

class Model {
 public:
  Model(Maze *m, MazeParser *mp, MazeGenerator *mg) 
      : maze_(m), maze_parser_(mp), maze_generator_(mg) {};
  void UploadMaze(std::string);
  Maze *GetMaze();
  void GenerateMaze(int, int);

 private:
  Maze *maze_;
  MazeParser *maze_parser_;
  MazeGenerator *maze_generator_;
};

}  // namespace s21

#endif  // A1_MAZE_1_SRC_MODELS_MODEL_H
