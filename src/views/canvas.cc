#include "canvas.h"

Canvas::Canvas(QWidget* parent) : QOpenGLWidget(parent) {}

void Canvas::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  s21::ControllerSingleton::GetInstance().InitOpenGL(s21::RenderType::MAZE);
}

void Canvas::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
}

void Canvas::paintGL() {
  s21::ControllerSingleton::GetInstance().PaintGL(s21::RenderType::MAZE);
}

void Canvas::UpdateWidget() {
  // update();
}
