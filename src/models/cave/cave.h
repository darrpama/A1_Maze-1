#ifndef A1_MAZE_1_0_SRC_MODEL_CAVE_H
#define A1_MAZE_1_0_SRC_MODEL_CAVE_H

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#include "../type.h"

namespace s21 {

class Cave {
 public:
  Cave(size_t rows, size_t cols) : rows_(rows), cols_(cols), matrix_{} {}
  Cave(Cave&& o) noexcept : rows_(o.rows_), cols_(o.cols_), matrix_(std::move(o.matrix_)) {}
  Cave(const Cave& o) : rows_(o.rows_), cols_(o.cols_), matrix_(o.matrix_) {}

  Cave& operator=(Cave&& other) noexcept {
    if (this != &other) {
      rows_ = other.rows_;
      cols_ = other.cols_;
      matrix_ = std::move(other.matrix_);
    }
    return *this;
  }

  Cave& operator=(const Cave& other) {
    if (this != &other) {
      rows_ = other.rows_;
      cols_ = other.cols_;
      matrix_ = other.matrix_;
    }
    return *this;
  }

  ~Cave() {}

  size_t GetRows();
  size_t GetCols();
  void SetRows(size_t);
  void SetCols(size_t);
  void Push(unsigned);
  std::vector<unsigned>& GetMatrix();
  void SetMatrix(std::vector<unsigned>);

  void Clear();

 private:
  size_t rows_;
  size_t cols_;
  std::vector<unsigned> matrix_;
};

}  // namespace s21

#endif  // A1_MAZE_1_0_SRC_MODEL_CAVE_H
