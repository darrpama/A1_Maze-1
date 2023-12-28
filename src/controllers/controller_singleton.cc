#include "controller_singleton.h"

namespace s21 {

void ControllerSingleton::SetModel(Model *model) { model_ = model; }

void ControllerSingleton::UploadMaze(const std::string &filepath) {
  model_->UploadMaze(filepath);
}

Maze *ControllerSingleton::GetMaze() { return model_->GetMaze(); }

void ControllerSingleton::GenerateMaze(int rows, int cols) {
  model_->GenerateMaze(rows, cols);
}

void ControllerSingleton::UploadCave(const std::string &filepath) {
  model_->UploadCave(filepath);
}

Cave *ControllerSingleton::GetCave() { return model_->GetCave(); }

void ControllerSingleton::GenerateCave(size_t rows, size_t cols, float chance) {
  model_->GenerateCave(rows, cols, chance);
}

bool ControllerSingleton::StepRender(unsigned die_limit, unsigned born_limit) {
  return model_->StepRender(die_limit, born_limit);
}

}  // namespace s21
