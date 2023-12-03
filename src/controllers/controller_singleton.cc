#include "controller_singleton.h"

namespace s21 {

void ControllerSingleton::InitOpenGL(RenderType type) {
  model_->InitOpenGL(type);
}

void ControllerSingleton::PaintGL(RenderType type) {
  model_->PaintGL(type);
}

}  // namespace s21