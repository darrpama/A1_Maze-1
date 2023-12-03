#ifndef A1_MAZE_1_SRC_CONTROLLERS_CONTROLLER_H
#define A1_MAZE_1_SRC_CONTROLLERS_CONTROLLER_H

#include "../models/model.h"

namespace s21 {

class Controller {
 public:
  Controller(Model *model) : model_(model) {};
 private:
  Model *model_;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLERS_CONTROLLER_H
