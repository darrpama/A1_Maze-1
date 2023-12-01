#ifndef A1_MAZE_1_SRC_CONTROLLERS_CONTROLLER_H
#define A1_MAZE_1_SRC_CONTROLLERS_CONTROLLER_H

#include "../models/model.h"

namespace s21 {

class Controller {
 public:
  Controller(Model *m) : model_(m) {}

 private:
  Model *model_;
};

}  // namespace s21

#endif  // A1_MAZE_1_SRC_CONTROLLERS_CONTROLLER_H