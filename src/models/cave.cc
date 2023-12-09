#include "cave.h"

namespace s21 {

int Cave::GetRows() { return rows_; }

int Cave::GetCols() { return cols_; }

void Cave::SetRows(int rows) { rows_ = rows; }

void Cave::SetCols(int cols) { cols_ = cols; }

void Cave::Push(unsigned border) { matrix_.push_back(border); }

std::vector<unsigned>& Cave::GetMatrix() { return matrix_; }

void Cave::Clear() {
  matrix_.clear();
  rows_ = 0;
  cols_ = 0;
}

}  // namespace s21
