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

bool Maze::IsIdeal() {
  std::vector<bool> visited(this->matrix_.size(), false);
  visited[0] = true;

  std::queue<int> q;
  q.push(0);

  std::vector<int> directions = { 1, -cols_, -1, cols_ };

  while(!q.empty()) {
    int cur_cell = q.front();
    q.pop();

    for (auto direction : directions) {
      int neighbor_cell = cur_cell + direction;

      if (neighbor_cell >= 0 && neighbor_cell < matrix_.size() && !visited[neighbor_cell]) {
        int current_row = cur_cell / cols_;
        int current_col = cur_cell % cols_;
        int neighbor_row = neighbor_cell / cols_;
        int neighbor_col = neighbor_cell % cols_;
        Border current_border = matrix_[current_row * cols_ + current_col];
        Border neighbor_border = matrix_[neighbor_row * cols_ + neighbor_col];

        if (current_border == BOTH_BORDER && (direction == 1 || direction == cols_))
          continue;
        if (current_border == RIGHT_BORDER && direction == 1)
          continue;
        if (current_border == BOTTOM_BORDER && direction == cols_)
          continue;
        if (direction == -1 && (neighbor_row != current_row || (neighbor_border == RIGHT_BORDER || neighbor_border == BOTH_BORDER)))
          continue;
        if (direction == -cols_ && (neighbor_col != current_col || (neighbor_border == BOTTOM_BORDER || neighbor_border == BOTH_BORDER)))
          continue;

        visited[neighbor_cell] = true;
        q.push(neighbor_cell);
      }
    }
  }

  return std::all_of(visited.begin(), visited.end(), [](bool v) { return v; });
}

}  // namespace s21
