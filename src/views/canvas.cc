#include "canvas.h"

Canvas::Canvas(QWidget* parent) : QOpenGLWidget(parent) {
  cols_ = 4;
  rows_ = 3;
  cell_width_ = std::round(498.0f / cols_ - 2.0f);
  cell_height_ = std::round(498.0f / rows_ - 2.0f);
  maze_ = {
    0, 2, 3, 1,
    0, 1, 0, 1,
    3, 2, 3, 1
  };
}

void Canvas::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void Canvas::paintGL() {
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  setFixedSize(500, 500);

  QPainter p(this);  
  size_t index = 0;
  for (size_t i = 0; i < rows_; i++) {
    for (size_t j = 0; j < cols_; j++) {
      int wall = maze_[index];
      DrawCell(&p, i, j, wall);
      index++;
    }
  }

  p.fillRect(0, 0, 500, 2, Qt::black);
  p.fillRect(0, 0, 2, 500, Qt::black);
}

void Canvas::DrawCell(QPainter *p, size_t i, size_t j, int wall) {
  if (wall == 0) {  // 0 - нет границ 
    DrawCellBody(p, i, j);
  }
  if (wall == 1) {  // 1 - граница справа
    DrawCellBody(p, i, j);
    DrawRightWall(p, i, j);
  }
  if (wall == 2) {  // 2 - граница снизу
    DrawCellBody(p, i, j);
    DrawBottomWall(p, i, j);
  }
  if (wall == 3) {  // 3 - границы и снизу и справа
    DrawCellBody(p, i, j);
    DrawRightWall(p, i, j);
    DrawBottomWall(p, i, j);
  }
}

void Canvas::DrawCellBody(QPainter *p, size_t i, size_t j) {
  p->fillRect(
    (cell_width_ * j) + (j*2),
    (cell_height_ * i) + (i*2),
    cell_width_,
    cell_height_, 
    Qt::GlobalColor::white
  );
}

void Canvas::DrawRightWall(QPainter *p, size_t i, size_t j) {
  p->fillRect(
    (cell_width_ * j) + (j*2) + cell_width_,
    (cell_height_ * i) + (i*2),
    2,
    cell_height_,
    Qt::GlobalColor::darkBlue
  );
}

void Canvas::DrawBottomWall(QPainter *p, size_t i, size_t j) {
  p->fillRect(
    (cell_width_ * j) + (j*2),
    (cell_height_ * i) + (i*2) + cell_height_,
    cell_width_,
    2,
    Qt::GlobalColor::darkBlue
  );
}

void Canvas::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
}

void Canvas::UpdateWidget() {
  // update();
}
