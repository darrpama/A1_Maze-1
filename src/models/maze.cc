#include "maze.h"

namespace s21 {

int Maze::GetRows() { return rows_; }

int Maze::GetCols() { return cols_; }

void Maze::SetRows(int rows) { rows_ = rows; }

void Maze::SetCols(int cols) { cols_ = cols; }

void Maze::Push(Border border) { matrix_.push_back(border); }

std::vector<Border>& Maze::GetMatrix() { return matrix_; }

void Maze::Clear() {
  matrix_.clear();
  rows_ = 0;
  cols_ = 0;
}

}  // namespace s21