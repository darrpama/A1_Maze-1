#ifndef A1_MAZE_1_SRC_CONTROLLERS_CONTROLLER_SINGLETON_H
#define A1_MAZE_1_SRC_CONTROLLERS_CONTROLLER_SINGLETON_H

#include <string>

#include "../models/model.h"

namespace s21 {

class ControllerSingleton {
 public:
  static ControllerSingleton &GetInstance() {
    static ControllerSingleton instance;
    return instance;
  }
  void SetModel(Model *model);

  Maze *GetMaze();
  void UploadMaze(const std::string &filename);
  void GenerateMaze(int rows, int cols);

  void UploadCave(const std::string &filename);
  void GenerateCave(size_t rows, size_t cols, float chance);
  void StepRender(unsigned die_limit, unsigned born_limit);
  Cave *GetCave();

 private:
  Model *model_;

  ControllerSingleton() : model_(){};
  ControllerSingleton(const ControllerSingleton &);
  ControllerSingleton &operator=(const ControllerSingleton &) = delete;
};

}  // namespace s21

#endif  // A1_MAZE_1_SRC_CONTROLLERS_CONTROLLER_SINGLETON_H