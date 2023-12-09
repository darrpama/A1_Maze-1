#ifndef A1_MAZE_1_SRC_MODELS_MODEL_H
#define A1_MAZE_1_SRC_MODELS_MODEL_H

#include "../type.h"
#include "maze.h"
#include "maze_parser.h"
#include "maze_generator.h"
#include "cave.h"
#include "cave_parser.h"

namespace s21 {

class Model {
 public:
  Model(Maze *m, MazeParser *mp, MazeGenerator *mg, Cave *c, CaveParser *cp) 
      : maze_(m), maze_parser_(mp), maze_generator_(mg), cave_(c), cave_parser_(cp) {};
  void UploadMaze(std::string);
  Maze *GetMaze();
  void GenerateMaze(int, int);
  void UploadCave(std::string);
  Cave *GetCave();

 private:
  Maze *maze_;
  MazeParser *maze_parser_;
  MazeGenerator *maze_generator_;
  Cave *cave_;
  CaveParser *cave_parser_;
};

}  // namespace s21

#endif  // A1_MAZE_1_SRC_MODELS_MODEL_H
