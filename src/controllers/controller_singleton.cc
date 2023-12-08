#include "controller_singleton.h"

namespace s21 {

void ControllerSingleton::UploadMaze(std::string filepath) {
  model_->UploadMaze(filepath);
}

void ControllerSingleton::SetModel(Model *model) { 
  model_ = model; 
}

Maze *ControllerSingleton::GetMaze() { 
  return model_->GetMaze(); 
}

void ControllerSingleton::GenerateMaze(int rows, int cols) {
  model_->GenerateMaze(rows, cols);
}

}  // namespace s21