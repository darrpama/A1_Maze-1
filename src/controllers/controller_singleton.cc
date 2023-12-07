#include "controller_singleton.h"

namespace s21 {

void ControllerSingleton::UploadMaze(std::string filepath) {
  model_->UploadMaze(filepath);
}

}  // namespace s21