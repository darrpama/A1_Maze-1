#include "cave.h"

namespace s21 {

Cave& Cave::operator=(Cave&& other) noexcept {
  if (this != &other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = std::move(other.matrix_);
  }
  return *this;
}

Cave& Cave::operator=(const Cave& other) {
  if (this != &other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
  }
  return *this;
}

size_t Cave::GetRows() { return rows_; }

size_t Cave::GetCols() { return cols_; }

void Cave::SetRows(size_t rows) { rows_ = rows; }

void Cave::SetCols(size_t cols) { cols_ = cols; }

void Cave::Push(unsigned border) { matrix_.push_back(border); }

std::vector<unsigned>& Cave::GetMatrix() { return matrix_; }

void Cave::SetMatrix(std::vector<unsigned> matrix) {
  matrix_ = matrix;
}

void Cave::Clear() {
  matrix_.clear();
  rows_ = 0;
  cols_ = 0;
}

void Cave::Generate(size_t rows, size_t cols, float chance) {
  Clear();
  rows_ = rows;
  cols_ = cols;
  matrix_ = std::vector<unsigned>(rows * cols, 0);
  for (size_t row = 0; row < rows; row++) {
    for (size_t col = 0; col < cols; col++) {
      matrix_[row * cols + col] = (RandomChoice(chance)) ? 1 : 0;
    }
  }
}

bool Cave::RandomChoice(float chance) {
  std::mt19937 gen(std::random_device{}());
  std::bernoulli_distribution bd(chance);

  return bd(gen);
}

bool Cave::StepRender(unsigned die_limit, unsigned born_limit) {
  Cave old_cave = *this;

  int current_col = 0;
  int current_row = 0;
  unsigned alive_neighbors_count = 0;

  for (int row = 0; row < rows_; row++) {
    current_row = row;
    for (int col = 0; col < cols_; col++) {
      current_col = col;
      alive_neighbors_count = GetAliveNeigborsCount(current_row, current_col);
      if (matrix_[row * cols_ + col] == 1) {  
        // alive cell (death rule)
        if (alive_neighbors_count < die_limit) {
          matrix_[row * cols_ + col] = 0;
        }
      } else {  
        // death cell (alive rule)
        if (alive_neighbors_count > born_limit) {
          matrix_[row * cols_ + col] = 1;
        }
      }
    }
  }

  return CompareCaves(&old_cave, this);
}

bool Cave::CompareCaves(Cave *old_cave, Cave *new_cave) {
  if (old_cave->GetRows() != new_cave->GetRows()) {
    return false;
  }
  if (old_cave->GetCols() != new_cave->GetCols()) {
    return false;
  }
  for (size_t i = 0; i < old_cave->GetRows(); i++) {
    for (size_t j = 0; j < old_cave->GetCols(); j++) {
      bool old_cave_value = old_cave->GetMatrix()[i * old_cave->GetCols() + j];
      bool new_cave_value = new_cave->GetMatrix()[i * new_cave->GetCols() + j];
      if (old_cave_value != new_cave_value) {
        return false;
      }
    }
  }
  return true;
}

int Cave::GetAliveNeigborsCount(int current_row, int current_col) {
  return GetNorthWest(current_row, current_col) + GetNorth(current_row, current_col)
       + GetNorthEast(current_row, current_col) + GetEast(current_row, current_col)
       + GetSouthEast(current_row, current_col) + GetSouth(current_row, current_col)
       + GetSouthWest(current_row, current_col) + GetWest(current_row, current_col);
}

int Cave::GetNorthWest(int current_row, int current_col) {
  return (((current_row - 1) < 0) || ((current_col - 1) < 0)) ? 1 
    : GetMatrix()[(current_row - 1) * cols_ + (current_col - 1)];
}

int Cave::GetNorth(int current_row, int current_col) {
  return ((current_row - 1) < 0) ? 1 
    : matrix_[(current_row - 1) * cols_ + current_col];
}

int Cave::GetNorthEast(int current_row, int current_col) {
  return (((current_row - 1) < 0) || ((current_col + 1) >= cols_)) ? 1 
    : matrix_[(current_row - 1) * cols_ + (current_col + 1)];
}

int Cave::GetEast(int current_row, int current_col) {
  return ((current_col + 1) >= cols_) ? 1 
    : matrix_[current_row * cols_ + (current_col + 1)];
}

int Cave::GetSouthEast(int current_row, int current_col) {
  return (((current_row + 1) >= rows_) || ((current_col + 1) >= cols_)) ? 1 
    : matrix_[(current_row + 1) * cols_ + (current_col + 1)];
}

int Cave::GetSouth(int current_row, int current_col) {
  return ((current_row + 1) >= rows_) ? 1 
    : matrix_[(current_row + 1) * cols_ + current_col];
}

int Cave::GetSouthWest(int current_row, int current_col) {
  return (((current_row + 1) >= rows_) || ((current_col - 1) < 0)) ? 1 
    : matrix_[(current_row + 1) * cols_ + (current_col - 1)];
}

int Cave::GetWest(int current_row, int current_col) {
  return ((current_col - 1) < 0) ? 1 
    : matrix_[current_row * cols_ + (current_col - 1)];
}

}  // namespace s21
