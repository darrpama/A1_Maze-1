#ifndef CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_CAVE_CANVAS_H
#define CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_CAVE_CANVAS_H

#include <QWidget>
#include <QPainter>

#include "../controllers/controller_singleton.h"
#include "../type.h"

class CaveCanvas : public QWidget {
 public:
  CaveCanvas(QWidget *parent = nullptr) : QWidget(parent) {}
  
 protected:
  void paintEvent(QPaintEvent *event) override;

 private:
  s21::Cave *cave_;
  int cols_;
  int rows_;
  int cell_width_ = 0;
  int cell_height_ = 0;

  void DrawCell(QPainter *p, size_t i, size_t j, unsigned cell);
  void DrawCellBody(QPainter *p, size_t i, size_t j, Qt::GlobalColor color);
};

#endif // CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_CAVE_CANVAS_H