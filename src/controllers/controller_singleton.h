#ifndef A1_MAZE_1_SRC_CONTROLLERS_CONTROLLER_SINGLETON_H
#define A1_MAZE_1_SRC_CONTROLLERS_CONTROLLER_SINGLETON_H

#include "../models/model.h"

namespace s21 {

class ControllerSingleton {
 public:
  static ControllerSingleton &GetInstance() {
    static ControllerSingleton instance;
    return instance;
  }
  void SetModel(Model *model) { model_ = model; }

 private:
  Model *model_;

  ControllerSingleton() : model_(){};
  ControllerSingleton(const ControllerSingleton &);
  ControllerSingleton &operator=(const ControllerSingleton &) = delete;
};

}  // namespace s21

#endif  // A1_MAZE_1_SRC_CONTROLLERS_CONTROLLER_SINGLETON_H