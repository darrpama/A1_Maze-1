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
  ~MazeCanvas();

 protected:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;

 private:
  QPainter *painter_;
  std::vector<s21::Border> matrix_;
  float width_;
  float height_;
  float border_size_;
  QColor border_color_;
  QColor frame_color_;
  QColor line_color_;
  QColor background_color_;
  
  float cell_width_ = 0.0f;
  float cell_height_ = 0.0f;
  int cols_ = 0;
  int rows_ = 0;
  int click_counter_ = 0;
  std::vector<s21::Vector2D> path_cells_;

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

#endif // CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAZE_CANVAS_H