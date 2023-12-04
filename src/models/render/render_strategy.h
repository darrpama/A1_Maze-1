#ifndef A1_MAZE_1_SRC_MODELS_RENDER_RENDER_STRATEGY_H
#define A1_MAZE_1_SRC_MODELS_RENDER_RENDER_STRATEGY_H

#include <QWidget>


namespace s21 {

class RenderStrategy {
 public:
  virtual void InitRender() = 0;
};

}  // namespace s21

#endif  // A1_MAZE_1_SRC_MODELS_RENDER_RENDER_STRATEGY_H
