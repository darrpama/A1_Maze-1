#include "controller_singleton.h"

namespace s21 {

void ControllerSingleton::SetModel(Model *model) { 
  model_ = model; 
}

void ControllerSingleton::UploadMaze(std::string filepath) {
  model_->UploadMaze(filepath);
}

Maze *ControllerSingleton::GetMaze() { 
  return model_->GetMaze(); 
}

void ControllerSingleton::GenerateMaze(int rows, int cols) {
  model_->GenerateMaze(rows, cols);
}

void ControllerSingleton::UploadCave(std::string filepath) {
  model_->UploadCave(filepath);
}

Cave *ControllerSingleton::GetCave() { 
  return model_->GetCave(); 
}

}  // namespace s21
