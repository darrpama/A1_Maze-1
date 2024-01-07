#ifndef CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_CAVE_CANVAS_H
#define CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_CAVE_CANVAS_H

#include <QPainter>
#include <QWidget>

#include "../controllers/controller_singleton.h"

class CaveCanvas : public QWidget {
 public:
  explicit CaveCanvas(QWidget *parent = nullptr);
  ~CaveCanvas();

  const float kBorderSize;

 protected:
  void paintEvent(QPaintEvent *event) override;

 private:
  QPainter *painter_;
  std::vector<unsigned> matrix_;

  float width_;
  float height_;

  float cell_width_;
  float cell_height_;

  int cols_;
  int rows_;

  void DrawFrames();
  void DrawCave();
  void DrawCell(size_t i, size_t j, unsigned cell);
};

#endif  // CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_CAVE_CANVAS_H
