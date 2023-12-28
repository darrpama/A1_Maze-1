#ifndef CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAZE_CANVAS_H
#define CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAZE_CANVAS_H

#include <QWidget>
#include <QPainter>

#include "../controllers/controller_singleton.h"
#include "../type.h"

class MazeCanvas : public QWidget {
 public:
  MazeCanvas(QWidget *parent = nullptr) : QWidget(parent) {}
  
 protected:
  void paintEvent(QPaintEvent *event) override;

 private:
  s21::Maze *maze_;
  int cols_;
  int rows_;
  double cell_width_ = 0;
  double cell_height_ = 0;

  void DrawCell(QPainter *p, size_t i, size_t j, s21::Border border);
  void DrawCellBody(QPainter *p, size_t i, size_t j);
  void DrawRightBorder(QPainter *p, size_t i, size_t j);
  void DrawBottomBorder(QPainter *p, size_t i, size_t j);
};

#endif // CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAZE_CANVAS_H