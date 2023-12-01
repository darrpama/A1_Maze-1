#include "maze.h"

namespace s21 {

std::vector<MazeStatement> Maze::GetMazeStatement() {

}

void Maze::SetMazeStatement(std::vector<MazeStatement> &maze_statement) {
  *maze_statement_ = maze_statement;
}

int Maze::GetRows() {
  return rows_;
}

int Maze::GetCols() {
  return cols_;
}

void Maze::SetRows(int rows) {
  rows_ = rows;
}

void Maze::SetCols(int cols) {
  cols_ = cols;
}

void Maze::Clear() {
  maze_statement_->clear();
  rows_ = 0;
  cols_ = 0;
}

}  // namespace s21