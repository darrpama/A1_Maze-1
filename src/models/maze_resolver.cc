#include "maze_resolver.h"

namespace s21 {

std::vector<std::pair<size_t, size_t>> MazeResolver::Resolve(std::pair<size_t, size_t> init_point, std::pair<size_t, size_t> end_point) {
  std::vector<std::pair<size_t, size_t>> solution{};
  int cols = maze_->GetCols();
  int rows = maze_->GetRows();
  int matrix_size = maze_->GetMatrix().size();

  std::vector<int> visited(matrix_size, -1);

  int init_cell = init_point.first * cols + init_point.second;
  int end_cell = end_point.first * cols + end_point.second;

  std::cout << init_cell << std::endl;
  std::cout << end_cell << std::endl;

  visited[init_cell] = 0;

  std::vector<int> directions = { 1, -cols, -1, cols };

  std::queue<int> q;
  q.push(init_cell);

  while(!q.empty()) {
    int cur_cell = q.front();
    q.pop();


    for (auto direction : directions) {
      int neighbor_cell = cur_cell + direction;

      if (neighbor_cell >= 0 && neighbor_cell < matrix_size && visited[neighbor_cell] == -1) {
        int current_row = cur_cell / cols;
        int current_col = cur_cell % cols;
        int neighbor_row = neighbor_cell / cols;
        int neighbor_col = neighbor_cell % cols;
        Border current_border = maze_->GetMatrix()[current_row * cols + current_col];
        Border neighbor_border = maze_->GetMatrix()[neighbor_row * cols + neighbor_col];

        if (current_border == BOTH_BORDER && (direction == 1 || direction == cols))
          continue;
        if (current_border == RIGHT_BORDER && direction == 1)
          continue;
        if (current_border == BOTTOM_BORDER && direction == cols)
          continue;
        if (direction == -1 && (neighbor_row != current_row || (neighbor_border == RIGHT_BORDER || neighbor_border == BOTH_BORDER)))
          continue;
        if (direction == -cols && (neighbor_col != current_col || (neighbor_border == BOTTOM_BORDER || neighbor_border == BOTH_BORDER)))
          continue;
        if (cur_cell == end_cell) {
          visited[neighbor_cell] = visited[cur_cell] + 1;
          break;
        }
        
        visited[neighbor_cell] = visited[cur_cell] + 1;
        q.push(neighbor_cell);
      }
    }

    for (int i = 0; i < matrix_size; i++) {
      std::cout << visited[i] << '\t';
      if ((i + 1) % cols == 0) {
        std::cout << std::endl;
      }
    }
    std::cout << std::endl;
  }

  return solution;
}

}  // namespace s21
