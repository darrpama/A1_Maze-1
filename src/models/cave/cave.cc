#include "cave.h"

namespace s21 {

Cave::Cave() : matrix_{}, rows_{}, cols_{}, die_limit_{}, born_limit_{} {}

Cave::Cave(int rows, int cols)
      : matrix_{}, rows_(rows), cols_(cols), die_limit_{}, born_limit_{} {}

int Cave::GetRows() { return rows_; }

int Cave::GetCols() { return cols_; }

void Cave::SetRows(int rows) { rows_ = rows; }

void Cave::SetCols(int cols) { cols_ = cols; }

std::vector<unsigned>& Cave::GetMatrix() { return matrix_; }

void Cave::Clear() {
  matrix_.clear();
  rows_ = 0;
  cols_ = 0;
}

void Cave::Generate(int rows, int cols, float chance) {
  Clear();
  rows_ = rows;
  cols_ = cols;
  matrix_ = std::vector<unsigned>(rows * cols, 0);

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      matrix_[row * cols + col] = (Utils::RandomChoice(chance)) ? 1 : 0;
    }
  }
}

bool Cave::StepRender(unsigned die_limit, unsigned born_limit) {
  Cave old_cave = *this;
  die_limit_ = die_limit;
  born_limit_ = born_limit;

  for (int row = 0; row < rows_; row++) {
    int current_row = row;
    for (int col = 0; col < cols_; col++) {
      int current_col = col;
      unsigned index = row * cols_ + col;
      ApplyRules(index,
                 GetAliveNeigborsCount(&old_cave, current_row, current_col));
    }
  }

  return CompareCaves(&old_cave, this);
}

void Cave::ApplyRules(unsigned index, unsigned alive_neighbors_count) {
  // alive cell (death rule)
  if (matrix_[index] == 1) {
    if (alive_neighbors_count < die_limit_) {
      matrix_[index] = 0;
    }
    // death cell (alive rule)
  } else {
    if (alive_neighbors_count > born_limit_) {
      matrix_[index] = 1;
    }
  }
}

bool Cave::CompareCaves(Cave *old_cave, Cave *new_cave) {
  if (old_cave->GetRows() != new_cave->GetRows() ||
      old_cave->GetCols() != new_cave->GetCols()) {
    return false;  // LCOV_EXCL_LINE
  }

  for (int i = 0; i < old_cave->GetRows(); i++) {
    for (int j = 0; j < old_cave->GetCols(); j++) {
      bool old_cave_value = old_cave->GetMatrix()[i * old_cave->GetCols() + j];
      bool new_cave_value = new_cave->GetMatrix()[i * new_cave->GetCols() + j];

      if (old_cave_value != new_cave_value) {
        return false;
      }
    }
  }

  return true;
}

int Cave::GetAliveNeigborsCount(Cave *cave, int r, int c) {
  int top_left = ((((r - 1) < 0) || ((c - 1) < 0))
                      ? 1
                      : cave->GetMatrix()[(r - 1) * cols_ + (c - 1)]);

  int top = (((r - 1) < 0) ? 1 : cave->GetMatrix()[(r - 1) * cols_ + c]);

  int top_right = ((((r - 1) < 0) || ((c + 1) >= cols_))
                       ? 1
                       : cave->GetMatrix()[(r - 1) * cols_ + (c + 1)]);

  int right = (((c + 1) >= cols_) ? 1 : cave->GetMatrix()[r * cols_ + (c + 1)]);

  int bottom_right = ((((r + 1) >= rows_) || ((c + 1) >= cols_))
                          ? 1
                          : cave->GetMatrix()[(r + 1) * cols_ + (c + 1)]);

  int bottom =
      (((r + 1) >= rows_) ? 1 : cave->GetMatrix()[(r + 1) * cols_ + c]);

  int bottom_left = (((r + 1) >= rows_) || ((c - 1) < 0))
                        ? 1
                        : cave->GetMatrix()[(r + 1) * cols_ + (c - 1)];

  int left = (((c - 1) < 0) ? 1 : cave->GetMatrix()[r * cols_ + (c - 1)]);

  return top_left + top + top_right + right + bottom_right + bottom +
         bottom_left + left;
}

// PARSER
// ==================================================================
void Cave::ParseFromFile(std::string filepath) {
  Clear();
  Utils::CheckAndFixEndLine(filepath);

  std::ifstream file(filepath);
  if (!file.is_open()) {
    throw std::invalid_argument("Failed to open file: " +
                                filepath);  // LCOV_EXCL_LINE
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string file_content = buffer.str();
  size_t pos = 0;
  size_t file_content_size = file_content.size();
  int current_line = 0;

  while (pos < file_content_size) {
    size_t line_end = file_content.find('\n', pos);
    std::string line = file_content.substr(pos, line_end - pos);
    if (current_line == 0) {
      ParseSize(line);
    } else {
      ParseMatrix(line);
    }
    current_line++;
    pos = line_end + 1;
  }

  file.close();
}

void Cave::ParseSize(const std::string &line) {
  std::stringstream ss(line);
  int rows, cols;

  if (ss >> rows >> cols) {
    SetRows(rows);
    SetCols(cols);
  } else {
    throw std::invalid_argument(
        "Failed to parse size of matrix");  // LCOV_EXCL_LINE
  }
}

void Cave::ParseMatrix(const std::string &line) {
  for (size_t i = 0; i < line.size(); i++) {
    if (line[i] == '0') {
      matrix_.push_back(0);
    } else if (line[i] == '1') {
      matrix_.push_back(1);
    }
  }
}

}  // namespace s21
