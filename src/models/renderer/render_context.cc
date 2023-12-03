#include "render_context.h"

namespace s21 {

void RenderContext::InitOpenGL() {
  strategy_->InitOpenGL();
}

void RenderContext::PaintGL() {
  strategy_->PaintGL();
}

}  // namespace s21
