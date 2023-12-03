#ifndef A1_MAZE_1_SRC_MODELS_RENDER_RENDER_CONTEXT_H
#define A1_MAZE_1_SRC_MODELS_RENDER_RENDER_CONTEXT_H

#include "render_strategy.h"

namespace s21 {

class RenderContext {
 public:
  RenderContext() {}
  explicit RenderContext(RenderStrategy *strategy) : strategy_(strategy) {}
  void SetStrategy(RenderStrategy *strategy) { strategy_ = strategy; }
  // methods
  void InitOpenGL();
  void PaintGL();

 private:
  RenderStrategy *strategy_;
};

}  // namespace s21

#endif  // A1_MAZE_1_SRC_MODELS_RENDER_RENDER_CONTEXT_H
