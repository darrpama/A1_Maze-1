#ifndef CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAZE_CANVAS_H
#define CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAZE_CANVAS_H

#include <QMouseEvent>
#include <QPainter>
#include <QWidget>
#include <vector>

#include "../controllers/controller_singleton.h"

class MazeCanvas : public QWidget {
 public:
  explicit MazeCanvas(QWidget *parent = nullptr);
  ~MazeCanvas();
  void ClearPath(int rows, int cols);

  const float kBorderSize;

 protected:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;

 private:
  QPainter *painter_;
  std::vector<s21::Border> matrix_;
  std::vector<s21::Vector2D> path_cells_;

  QColor border_color_;
  QColor frame_color_;
  QColor line_color_;
  QColor background_color_;

  float cell_width_;
  float cell_height_;

  int cols_;
  int rows_;
  int click_counter_;

  void DrawMaze();
  void DrawBackground();
  void DrawFrames();
  void DrawPath();
  void DrawCell(size_t i, size_t j, s21::Border border);
  void DrawCellBody(size_t i, size_t j);
  void DrawClickedCellBody();
  void DrawRightBorder(size_t i, size_t j);
  void DrawBottomBorder(size_t i, size_t j);
  void DrawPathLine();
  void DrawLineBetweenCellsCenters(s21::Vector2D, s21::Vector2D);
};

#endif  // CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAZE_CANVAS_H
