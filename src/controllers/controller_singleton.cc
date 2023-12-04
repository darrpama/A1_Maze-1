#include "controller_singleton.h"

namespace s21 {

void ControllerSingleton::InitRender(RenderType type) {
  model_->InitRender(type);
}

void ControllerSingleton::Render(RenderType type) {
  model_->Render(type);
}

}  // namespace s21