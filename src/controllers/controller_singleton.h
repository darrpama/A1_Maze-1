#ifndef A1_MAZE_1_SRC_CONTROLLERS_CONTROLLER_SINGLETON_H
#define A1_MAZE_1_SRC_CONTROLLERS_CONTROLLER_SINGLETON_H

#include <string>

#include "../models/cave/cave.h"
#include "../models/maze/maze.h"
#include "../models/maze/maze_generator.h"
#include "../models/maze/maze_parser.h"
#include "../models/maze/maze_saver.h"
#include "../models/type.h"

namespace s21 {

class ControllerSingleton {
 public:
  static ControllerSingleton &GetInstance() {
    static ControllerSingleton instance;
    return instance;
  }

  void SetMaze(Maze *m);
  void SetMazeParser(MazeParser *mp);
  void SetMazeGenerator(MazeGenerator *mg);
  void SetMazeSaver(MazeSaver *mg);
  void SetCave(Cave *c);

  void UploadMaze(const std::string &filename);
  void DownloadMaze(const std::string &filename);
  void GenerateMaze(int rows, int cols);
  std::vector<Vector2D> ResolveMaze(Vector2D, Vector2D);
  std::vector<Border> &GetMazeMatrix();
  int GetMazeRows();
  int GetMazeCols();

  void UploadCave(const std::string &filename);
  void GenerateCave(int rows, int cols, float chance);
  bool StepRender(unsigned die_limit, unsigned born_limit);
  std::vector<unsigned> &GetCaveMatrix();
  int GetCaveRows();
  int GetCaveCols();

 private:
  Maze *maze_;
  MazeParser *maze_parser_;
  MazeGenerator *maze_generator_;
  MazeSaver *maze_saver_;
  Cave *cave_;

  ControllerSingleton()
      : maze_(nullptr),
        maze_parser_(nullptr),
        maze_generator_(nullptr),
        maze_saver_(nullptr),
        cave_(nullptr){};
  ControllerSingleton(const ControllerSingleton &);
  ControllerSingleton &operator=(const ControllerSingleton &) = delete;
};

}  // namespace s21

#endif  // A1_MAZE_1_SRC_CONTROLLERS_CONTROLLER_SINGLETON_H