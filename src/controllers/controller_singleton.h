#ifndef A1_MAZE_1_SRC_CONTROLLERS_CONTROLLER_SINGLETON_H
#define A1_MAZE_1_SRC_CONTROLLERS_CONTROLLER_SINGLETON_H

#include <string>

#include "models/type.h"
#include "models/cave/cave.h"
#include "models/maze/maze.h"
#include "models/maze/maze_generator.h"
#include "models/maze/maze_parser.h"

namespace s21 {

class ControllerSingleton {
 public:
  static ControllerSingleton &GetInstance() {
    static ControllerSingleton instance;
    return instance;
  }

  void SetMaze(Maze *m) { maze_ = m; }
  void SetMazeParser(MazeParser *mp) { maze_parser_ = mp; }
  void SetMazeGenerator(MazeGenerator *mg) { maze_generator_ = mg; }
  void SetCave(Cave *c) { cave_ = c; }

  std::vector<Border> &GetMazeMatrix();
  int GetMazeRows();
  int GetMazeCols();
  void UploadMaze(const std::string &filename);
  void GenerateMaze(int rows, int cols);
  std::vector<Vector2D> ResolveMaze(Vector2D, Vector2D);

  std::vector<unsigned> &GetCaveMatrix();
  int GetCaveRows();
  int GetCaveCols();
  void UploadCave(const std::string &filename);
  void GenerateCave(size_t rows, size_t cols, float chance);
  bool StepRender(unsigned die_limit, unsigned born_limit);

 private:
  Maze *maze_;
  MazeParser *maze_parser_;
  MazeGenerator *maze_generator_;
  Cave *cave_;

  ControllerSingleton() {};
  ControllerSingleton(const ControllerSingleton &);
  ControllerSingleton &operator=(const ControllerSingleton &) = delete;
};

}  // namespace s21

#endif  // A1_MAZE_1_SRC_CONTROLLERS_CONTROLLER_SINGLETON_H