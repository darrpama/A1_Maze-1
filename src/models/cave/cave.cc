#include "cave.h"

namespace s21 {

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

}  // namespace s21
