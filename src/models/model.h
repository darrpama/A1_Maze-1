#ifndef A1_MAZE_1_SRC_MODELS_MODEL_H
#define A1_MAZE_1_SRC_MODELS_MODEL_H

#include "renderer.h"

namespace s21 {

class Model {
 public:
  explicit Model(Renderer *renderer) : renderer_(renderer) {}
 private:
  Renderer *renderer_;
};

}  // namespace s21

#endif  // A1_MAZE_1_SRC_MODELS_MODEL_H
