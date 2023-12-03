#include "model.h"

namespace s21 {
void Model::InitOpenGL(RenderType type) {
  if (type == RenderType::MAZE) {
    render_context_->SetStrategy(new MazeRenderStrategy());
  } else if (type == RenderType::CAVE) {
    // context.SetStrategy(new CaveRenderStrategy());
  } else {
    // context.SetStrategy(new CaveRenderStrategy());
  }
  render_context_->InitOpenGL();
}

void Model::PaintGL(RenderType type) {
  if (type == RenderType::MAZE) {
    render_context_->SetStrategy(new MazeRenderStrategy());
  } else if (type == RenderType::CAVE) {
    // context.SetStrategy(new CaveRenderStrategy());
  } else {
    // context.SetStrategy(new CaveRenderStrategy());
  }
  render_context_->PaintGL();
}

}  // namespace s21
