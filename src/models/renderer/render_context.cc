#include "render_context.h"

namespace s21 {

void RenderContext::Draw() {
  strategy_->Draw();
}

}  // namespace s21
