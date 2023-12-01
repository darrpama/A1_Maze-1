#include "canvas.h"

Canvas::Canvas(QWidget* parent)
    : QOpenGLWidget(parent) {
  
  cols_ = 4;
  rows_ = 4;
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
  setFixedSize(500,500);

  QPainter p(this);

  p.fillRect(0, 0, 500, 2, Qt::black);
  p.fillRect(0, 0, 2, 500, Qt::black);
  p.fillRect(0, 498, 500, 2, Qt::black);
  p.fillRect(498, 0, 2, 500, Qt::black);
  p.setPen(Qt::black);
  p.drawLine(0,0,500,0);
  p.drawLine(0,0,0,500);
  p.setPen(Qt::blue);
  p.setPen(Qt::red);
  p.drawLine(100,200,300,400);
}

void Canvas::resizeGL(int w, int h) {
  // s21::Controller::GetInstance().SetViewPort(w, h);
  glViewport(0, 0, w, h);
}

void Canvas::UpdateWidget() {
  update();
}

void Canvas::DrawCell() {
  
}