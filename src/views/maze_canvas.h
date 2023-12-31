#ifndef CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAZE_CANVAS_H
#define CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAZE_CANVAS_H

#include <vector>

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

#include "../controllers/controller_singleton.h"

class MazeCanvas : public QWidget {
 public:
  MazeCanvas(QWidget *parent = nullptr);

 protected:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;

 private:
  QPainter *painter_;
  std::vector<s21::Border> matrix_;
  float width_;
  float height_;
  float border_size_;
  double cell_width_ = 0.0f;
  double cell_height_ = 0.0f;
  int cols_ = 0;
  int rows_ = 0;
  int click_counter_ = 0;
  std::vector<s21::Vector2D> path_cells_;

  void DrawMaze();
  void DrawFrames();
  void DrawPath();
  void DrawCell(size_t i, size_t j, s21::Border border);
  void DrawCellBody(size_t i, size_t j);
  void DrawClickedCellBody();
  void DrawRightBorder(size_t i, size_t j);
  void DrawBottomBorder(size_t i, size_t j);
  void DrawPathLine();
  void DrawLineBetweenCellsCenters(size_t row_1, size_t col_1, size_t row_2, size_t col_2);
};

#endif // CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAZE_CANVAS_H