#ifndef A1_MAZE_1_SRC_MODELS_MODEL_H
#define A1_MAZE_1_SRC_MODELS_MODEL_H

#include "type.h"
#include "cave/cave.h"
#include "cave/cave_generator.h"
#include "cave/cave_parser.h"
#include "maze/maze.h"
#include "maze/maze_generator.h"
#include "maze/maze_parser.h"

namespace s21 {

class Model {
 public:
  Model(Maze *m, MazeParser *mp, MazeGenerator *mg, Cave *c, CaveParser *cp,
        CaveGenerator *cg);

  void UploadMaze(const std::string &);
  std::vector<Border> &GetMazeMatrix();
  int GetMazeRows();
  int GetMazeCols();
  void GenerateMaze(int, int);
  std::vector<Vector2D> ResolveMaze(Vector2D, Vector2D);

  void UploadCave(const std::string &);
  std::vector<unsigned> &GetCaveMatrix();
  int GetCaveRows();
  int GetCaveCols();
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
