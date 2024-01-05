#include "controller_singleton.h"

namespace s21 {

// INIT
void ControllerSingleton::SetMaze(Maze *m) { maze_ = m; }

void ControllerSingleton::SetMazeParser(MazeParser *mp) { maze_parser_ = mp; }

void ControllerSingleton::SetMazeGenerator(MazeGenerator *mg) {
  maze_generator_ = mg;
}

void ControllerSingleton::SetCave(Cave *c) { cave_ = c; }

// MAZE
void ControllerSingleton::UploadMaze(const std::string &filepath) {
  maze_parser_->SetFilePath(filepath);
  maze_parser_->Parse();
}

void ControllerSingleton::GenerateMaze(int rows, int cols) {
  maze_->Clear();
  Maze maze = maze_generator_->GenerateMaze(rows, cols);
  maze_->SetCols(maze.GetCols());
  maze_->SetRows(maze.GetRows());
  maze_->GetMatrix() = maze.GetMatrix();
}

std::vector<Vector2D> ControllerSingleton::ResolveMaze(Vector2D a, Vector2D b) {
  return maze_->Resolve(a, b);
}

std::vector<Border> &ControllerSingleton::GetMazeMatrix() {
  return maze_->GetMatrix();
}

int ControllerSingleton::GetMazeRows() { return maze_->GetCols(); }

int ControllerSingleton::GetMazeCols() { return maze_->GetRows(); }

// CAVE
void ControllerSingleton::UploadCave(const std::string &filepath) {
  cave_->ParseFromFile(filepath);
}

void ControllerSingleton::GenerateCave(int rows, int cols, float chance) {
  cave_->Generate(rows, cols, chance);
}

bool ControllerSingleton::StepRender(unsigned die_limit, unsigned born_limit) {
  return cave_->StepRender(die_limit, born_limit);
}

std::vector<unsigned> &ControllerSingleton::GetCaveMatrix() {
  return cave_->GetMatrix();
}

int ControllerSingleton::GetCaveRows() { return cave_->GetCols(); }

int ControllerSingleton::GetCaveCols() { return cave_->GetRows(); }

}  // namespace s21
