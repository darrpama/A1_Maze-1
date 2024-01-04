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

  std::vector<int> directions = {1, -cols_, -1, cols_};

  while (!q.empty()) {
    int cur_cell = q.front();
    int current_row = cur_cell / cols_;
    int current_col = cur_cell % cols_;
    q.pop();

    for (auto direction : directions) {
      int neighbor_cell = cur_cell + direction;
      int neighbor_row = neighbor_cell / cols_;
      int neighbor_col = neighbor_cell % cols_;

      if (neighbor_cell >= 0 && neighbor_cell < (int)matrix_.size() &&
          !visited[neighbor_cell]) {
        Border current_border = matrix_[current_row * cols_ + current_col];
        Border neighbor_border = matrix_[neighbor_row * cols_ + neighbor_col];

        if (CheckBorder(direction, current_border, neighbor_border, current_row,
                        current_col, neighbor_row, neighbor_col)) {
          continue;
        }

        visited[neighbor_cell] = true;
        q.push(neighbor_cell);
      }
    }
  }

  return std::all_of(visited.begin(), visited.end(), [](bool v) { return v; });
}

std::vector<Vector2D> Maze::Resolve(Vector2D start_point, Vector2D end_point) {
  std::vector<int> visited = FindPath(start_point, end_point);
  return (FindSolution(start_point, end_point, visited));
}

bool Maze::CheckBorder(int dir, int c_b, int n_b, int c_r, int c_c, int n_r,
                       int n_c) {
  bool answer = false;
  if (c_b == BOTH_BORDER && (dir == 1 || dir == cols_)) answer = true;
  if (c_b == RIGHT_BORDER && dir == 1) answer = true;
  if (c_b == BOTTOM_BORDER && dir == cols_) answer = true;
  if (dir == -1 && (n_r != c_r || (n_b == RIGHT_BORDER || n_b == BOTH_BORDER)))
    answer = true;
  if (dir == -cols_ &&
      (n_c != c_c || (n_b == BOTTOM_BORDER || n_b == BOTH_BORDER)))
    answer = true;
  return answer;
}

std::vector<int> Maze::FindPath(Vector2D init_point, Vector2D end_point) {
  int matrix_size = GetMatrix().size();
  int init_cell = init_point.x_ * cols_ + init_point.y_;
  int end_cell = end_point.x_ * cols_ + end_point.y_;
  std::vector<int> visited(matrix_size, -1);
  visited[init_cell] = 0;
  std::vector<int> directions = {1, -cols_, -1, cols_};
  std::queue<int> q;
  q.push(init_cell);

  while (!q.empty()) {
    int cur_cell = q.front();
    int current_row = cur_cell / cols_;
    int current_col = cur_cell % cols_;
    q.pop();

    for (auto direction : directions) {
      int neighbor_cell = cur_cell + direction;

      if (neighbor_cell >= 0 && neighbor_cell < matrix_size &&
          visited[neighbor_cell] == -1) {
        int neighbor_row = neighbor_cell / cols_;
        int neighbor_col = neighbor_cell % cols_;
        Border current_border = GetMatrix()[current_row * cols_ + current_col];
        Border neighbor_border =
            GetMatrix()[neighbor_row * cols_ + neighbor_col];

        if (CheckBorder(direction, current_border, neighbor_border, current_row,
                        current_col, neighbor_row, neighbor_col)) {
          continue;
        }

        q.push(neighbor_cell);
        if (cur_cell == end_cell) {
          while (!q.empty()) {
            q.pop();
          }
          break;
        }
        visited[neighbor_cell] = visited[cur_cell] + 1;
      }
    }
  }
  return visited;
}

std::vector<Vector2D> Maze::FindSolution(Vector2D init_point,
                                         Vector2D end_point,
                                         const std::vector<int>& visited) {
  int matrix_size = GetMatrix().size();
  int init_cell = init_point.x_ * cols_ + init_point.y_;
  int end_cell = end_point.x_ * cols_ + end_point.y_;
  std::vector<Vector2D> solution{};
  solution.reserve(matrix_size);
  if (init_point.x_ == end_point.x_ && init_point.y_ == end_point.y_) {
    solution.push_back(init_point);
    solution.push_back(end_point);
    return solution;
  }
  std::vector<int> directions = {1, -cols_, -1, cols_};
  std::queue<int> q;
  q.push(end_cell);
  solution.push_back(Vector2D(end_point.x_, end_point.y_));

  while (!q.empty()) {
    int cur_cell = q.front();
    int current_row = cur_cell / cols_;
    int current_col = cur_cell % cols_;
    q.pop();

    for (auto direction : directions) {
      int neighbor_cell = cur_cell + direction;
      int neighbor_row = neighbor_cell / cols_;
      int neighbor_col = neighbor_cell % cols_;
      Border current_border = GetMatrix()[current_row * cols_ + current_col];
      Border neighbor_border = GetMatrix()[neighbor_row * cols_ + neighbor_col];

      if (CheckBorder(direction, current_border, neighbor_border, current_row,
                      current_col, neighbor_row, neighbor_col)) {
        continue;
      }

      if (visited[cur_cell] - visited[neighbor_cell] == 1) {
        q.push(neighbor_cell);
        solution.push_back(Vector2D(neighbor_row, neighbor_col));
      }
      if (cur_cell == init_cell) {
        while (!q.empty()) {
          q.pop();
        }
        break;
      }
    }
  }
  return solution;
}

}  // namespace s21
