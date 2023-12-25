#ifndef CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAZE_CANVAS_H
#define CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAZE_CANVAS_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

#include "../controllers/controller_singleton.h"
#include "../type.h"

class MazeCanvas : public QWidget {
 public:
  MazeCanvas(QWidget *parent = nullptr) : QWidget(parent) {}

  
 protected:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;

 private:
  s21::Maze *maze_;
  int cols_;
  int rows_;
  int cell_width_ = 0;
  int cell_height_ = 0;
  int click_counter_ = 0;
  std::vector<std::pair<int, int>> cells_;

  void DrawCell(QPainter *p, size_t i, size_t j, s21::Border border);
  void DrawCellBody(QPainter *p, size_t i, size_t j);
  void DrawClickedCellBody(QPainter *p);
  void DrawRightBorder(QPainter *p, size_t i, size_t j);
  void DrawBottomBorder(QPainter *p, size_t i, size_t j);
  void DrawPathLine(QPainter *p);
  void DrawLineBetweenCellsCenters(QPainter *p, size_t row_1, size_t col_1, size_t row_2, size_t col_2);
};

#endif // CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAZE_CANVAS_H