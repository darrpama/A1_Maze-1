#ifndef A1_MAZE_1_SRC_MODELS_MODEL_H
#define A1_MAZE_1_SRC_MODELS_MODEL_H

#include "../type.h"
#include "cave.h"
#include "cave_generator.h"
#include "cave_parser.h"
#include "maze.h"
#include "maze_generator.h"
#include "maze_parser.h"

namespace s21 {

class Model {
 public:
  Model(Maze *m, MazeParser *mp, MazeGenerator *mg, Cave *c, CaveParser *cp,
        CaveGenerator *cg)
      : maze_(m),
        maze_parser_(mp),
        maze_generator_(mg),
        cave_(c),
        cave_parser_(cp),
        cave_generator_(cg){};

  void UploadMaze(const std::string &);
  Maze *GetMaze();
  void GenerateMaze(int, int);

  void UploadCave(const std::string &);
  Cave *GetCave();
  void GenerateCave(size_t, size_t, float chance);
  bool StepRender(unsigned die_limit, unsigned born_limit);

 private:
  Maze *maze_;
  MazeParser *maze_parser_;
  MazeGenerator *maze_generator_;
  Cave *cave_;
  CaveParser *cave_parser_;
  CaveGenerator *cave_generator_;
};

}  // namespace s21

#endif  // A1_MAZE_1_SRC_MODELS_MODEL_H
