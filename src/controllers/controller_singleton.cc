#include "controller_singleton.h"
#include "controller_singleton.h"

namespace s21 {

void ControllerSingleton::SetModel(Model *model) { model_ = model; }

// MAZE
void ControllerSingleton::UploadMaze(const std::string &filepath) {
  model_->UploadMaze(filepath);
}

std::vector<Border> &ControllerSingleton::GetMazeMatrix() { 
  return model_->GetMazeMatrix();
}

int ControllerSingleton::GetMazeRows() {
  return model_->GetMazeCols();
}
int ControllerSingleton::GetMazeCols() {
  return model_->GetMazeRows();
}

void ControllerSingleton::GenerateMaze(int rows, int cols) {
  model_->GenerateMaze(rows, cols);
}

std::vector<Vector2D> ControllerSingleton::ResolveMaze(Vector2D a, Vector2D b) {
  return model_->ResolveMaze(a, b);
}

// CAVE
void ControllerSingleton::UploadCave(const std::string &filepath) {
  model_->UploadCave(filepath);
}
std::vector<unsigned> &ControllerSingleton::GetCaveMatrix() {
  return model_->GetCaveMatrix();
}

int ControllerSingleton::GetCaveRows() {
  return model_->GetCaveCols();
}

int ControllerSingleton::GetCaveCols() {
  return model_->GetCaveRows();
}

void ControllerSingleton::GenerateCave(size_t rows, size_t cols, float chance) {
  model_->GenerateCave(rows, cols, chance);
}

bool ControllerSingleton::StepRender(unsigned die_limit, unsigned born_limit) {
  return model_->StepRender(die_limit, born_limit);
}


} // namespace s21
