#include "maze.h"

namespace s21 {

std::vector<MazeStatement> Maze::GetMazeStatement() {

}

void Maze::SetMazeStatement(std::vector<MazeStatement> &data) {

}

int Maze::GetRows() {
  return rows_;
}

int Maze::GetCols() {
  return cols_;
}

void Maze::SetRows(int rows) {

}

void Maze::SetCols(int cols) {

}

void Maze::Clear() {
  maze_statement_->clear();
  rows_ = 0;
  cols_ = 0;
}

}  // namespace s21