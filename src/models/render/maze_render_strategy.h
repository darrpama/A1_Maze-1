#ifndef A1_MAZE_1_SRC_MODELS_RENDER_MAZE_RENDER_STRATEGY_H
#define A1_MAZE_1_SRC_MODELS_RENDER_MAZE_RENDER_STRATEGY_H

#include <QPainter>
#include <QWidget>

#include <vector>
#include <utility>
#include <iostream>

#include "render_strategy.h"

namespace s21 {

class MazeRenderStrategy : public s21::RenderStrategy, public QWidget {
 public:
  MazeRenderStrategy(QWidget *parent = nullptr);
  void InitRender() override;

 protected:
  void paintEvent(QPaintEvent *event) override;

 private:
  std::vector<int> maze_;
  int cols_;
  int rows_;
  int cell_width_ = 0;
  int cell_height_ = 0;

  void DrawCell(QPainter *, size_t, size_t, int);
  void DrawCellBody(QPainter *p, size_t i, size_t j);
  void DrawRightWall(QPainter *, size_t, size_t);
  void DrawBottomWall(QPainter *, size_t, size_t);
};

}  // namespace s21

#endif  // A1_MAZE_1_SRC_MODELS_RENDER_MAZE_RENDER_STRATEGY_H
