#ifndef A1_MAZE_1_SRC_MODELS_RENDERER_MAZE_RENDERER_STRATEGY_H
#define A1_MAZE_1_SRC_MODELS_RENDERER_MAZE_RENDERER_STRATEGY_H

#include "render_strategy.h"

namespace s21 {

class MazeRenderStrategy : public RenderStrategy {
 public:
  void Draw() override;
};

}  // namespace s21

#endif  // A1_MAZE_1_SRC_MODELS_RENDERER_MAZE_RENDERER_STRATEGY_H
