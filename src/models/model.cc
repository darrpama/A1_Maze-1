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

  for (unsigned i = 0; i < cave_->GetMatrix().size(); i++) {
    std::cout << cave_->GetMatrix().at(i) << std::endl;
  }
}

Cave *Model::GetCave() {
  return cave_;
}

}  // namespace s21
