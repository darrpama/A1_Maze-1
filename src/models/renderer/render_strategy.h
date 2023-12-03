#ifndef A1_MAZE_1_SRC_MODELS_RENDERER_RENDER_STRATEGY_H
#define A1_MAZE_1_SRC_MODELS_RENDERER_RENDER_STRATEGY_H

#include <QtOpenGLWidgets/qopenglwidget.h>
#include <QOpenGLFunctions>


namespace s21 {

class RenderStrategy  : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
 public:
  virtual void InitOpenGL() = 0;
  virtual void PaintGL() = 0;
};

}  // namespace s21

#endif  // A1_MAZE_1_SRC_MODELS_RENDERER_RENDER_STRATEGY_H
