#include "model.h"

namespace s21 {

void Model::UploadMaze(std::string filepath) {
  maze_parser_->SetFilePath(filepath);
  maze_parser_->Parse();
}

Maze *Model::GetMaze() {
  return maze_;
}

void Model::GenerateMaze(int rows, int cols) {
  maze_->Clear();
  Maze maze = maze_generator_->GenerateMaze(rows, cols);
  maze_->SetCols(maze.GetCols());
  maze_->SetRows(maze.GetRows());
  maze_->GetMatrix() = maze.GetMatrix();
}

void Model::UploadCave(std::string filepath) {
  cave_parser_->SetFilePath(filepath);
  cave_parser_->Parse();
}

Cave *Model::GetCave() {
  return cave_;
}

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
