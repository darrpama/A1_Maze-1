#ifndef A1_MAZE_1_SRC_MODELS_MODEL_H
#define A1_MAZE_1_SRC_MODELS_MODEL_H

#include "render/render_context.h"
#include "render/maze_render_strategy.h"
#include "../type.h"


namespace s21 {

class Model {
 public:
  Model(RenderContext *rc) : render_context_(rc) {}
  void InitRender(RenderType type);
  void Render(RenderType type);

 private:
  RenderContext *render_context_;
};

}  // namespace s21

#endif  // A1_MAZE_1_SRC_MODELS_MODEL_H
