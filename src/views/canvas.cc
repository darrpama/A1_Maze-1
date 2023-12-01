#include "canvas.h"

Canvas::Canvas(QWidget* parent)
    : QOpenGLWidget(parent) {
  cols_ = 3;
  rows_ = 3;
  cell_width_ = std::ceilf(498.0f / cols_ - 2.0f);
  cell_height_ = std::ceilf(498.0f / rows_ - 2.0f);
  maze_ = {0, 2, 1, 0, 1, 1, 3, 2, 3};
}

void Canvas::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  // s21::Controller::GetInstance().InitOpenGL();
}

void Canvas::paintGL() {
  // s21::Controller::GetInstance().PaintGL();
  glClearColor(0.9, 0.8, 0.98, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  setFixedSize(500, 500);

  QPainter p(this);

  for (size_t i = 0; i < (cols_ * rows_); i++) {
    std::cout << i << std::endl;
    // todo draw cell with walls
  }
  

  // for (size_t i = 0; i < rows_; i++) {
  //   for (size_t j = 0; j < cols_; j++) {
  //     if (i % 2 == 0) {
  //       if (j % 2 == 0) {
  //         DrawCell(Qt::yellow, &p, i, j);
  //       } else if (j % 2 == 1) {
  //         DrawCell(Qt::red, &p, i, j);
  //       } else {
  //         DrawCell(Qt::red, &p, i, j);
  //       }
  //     } else if (i % 2 == 1) {
  //       if (j % 2 == 0) {
  //         DrawCell(Qt::green, &p, i, j);
  //       } else if (j % 2 == 1) {
  //         DrawCell(Qt::blue, &p, i, j);
  //       } else {
  //         DrawCell(Qt::blue, &p, i, j);
  //       }
  //     } else {
  //       DrawCell(Qt::blue, &p, i, j);
  //     }
  //   }
  // }

  p.fillRect(0, 0, 500, 2, Qt::black);
  p.fillRect(0, 0, 2, 500, Qt::black);
}

void Canvas::DrawCell(Qt::GlobalColor color, QPainter *p, size_t i, size_t j) {
  p->fillRect(
    (cell_width_ * j) + (j*2),
    (cell_height_ * i) + (i*2),
    cell_width_,
    cell_height_, 
    color
  );
}

void Canvas::resizeGL(int w, int h) {
  // s21::Controller::GetInstance().SetViewPort(w, h);
  glViewport(0, 0, w, h);
}

void Canvas::UpdateWidget() {
  // update();
}
