#ifndef CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_CAVE_CANVAS_H
#define CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_CAVE_CANVAS_H

#include <QWidget>
#include <QPainter>

#include "../controllers/controller_singleton.h"

class CaveCanvas : public QWidget {
 public:
  CaveCanvas(QWidget *parent = nullptr);
  ~CaveCanvas();
  
 protected:
  void paintEvent(QPaintEvent *event) override;

 private:
  QPainter *painter_;
  std::vector<unsigned> matrix_;
  float width_;
  float height_;
  float border_size_;
  float cell_width_ = 0;
  float cell_height_ = 0;
  int cols_ = 0;
  int rows_ = 0;

  void DrawFrames();
  void DrawCave();
  void DrawCell(size_t i, size_t j, unsigned cell);
};

#endif // CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_CAVE_CANVAS_H