#include "model.h"

namespace s21 {

// MAZE
void Model::UploadMaze(const std::string& filepath) {
  maze_parser_->SetFilePath(filepath);
  maze_parser_->Parse();
}

std::vector<Border> &Model::GetMazeMatrix() { 
  return maze_->GetMatrix();
}

int Model::GetMazeCols() {
  return maze_->GetCols();
}
int Model::GetMazeRows() {
  return maze_->GetRows();
}

void Model::GenerateMaze(int rows, int cols) {
  maze_->Clear();
  Maze maze = maze_generator_->GenerateMaze(rows, cols);
  maze_->SetCols(maze.GetCols());
  maze_->SetRows(maze.GetRows());
  maze_->GetMatrix() = maze.GetMatrix();
}

std::vector<Vector2D> Model::ResolveMaze(Vector2D a, Vector2D b) {
  return maze_->Resolve(a, b);
}

// CAVE
void Model::UploadCave(const std::string& filepath) {
  cave_parser_->SetFilePath(filepath);
  cave_parser_->Parse();
}

Cave* Model::GetCave() { return cave_; }

void Model::GenerateCave(size_t rows, size_t cols, float chance) {
  cave_->Clear();
  Cave cave = cave_generator_->Generate(rows, cols, chance);
  cave_->SetCols(cave.GetCols());
  cave_->SetRows(cave.GetRows());
  cave_->GetMatrix() = cave.GetMatrix();
}

bool Model::StepRender(unsigned die_limit, unsigned born_limit) {
  return cave_generator_->Step(cave_, die_limit, born_limit);
}

}  // namespace s21
