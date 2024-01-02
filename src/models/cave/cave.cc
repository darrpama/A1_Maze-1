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

  for (int row = 0; row < static_cast<int>(rows_); row++) {
    current_row = row;
    for (int col = 0; col < static_cast<int>(cols_); col++) {
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

int Cave::GetAliveNeigborsCount(int r, int c) {
  int top_left = ((((r-1) < 0) || ((c-1) < 0)) ? 1 : matrix_[(r-1) * cols_ + (c-1)]);
  int top = (((r-1) < 0) ? 1 : matrix_[(r-1) * cols_ + c]);
  int top_right = ((((r-1) < 0) || ((c+1) >= static_cast<int>(cols_))) ? 1 : matrix_[(r-1) * cols_ + (c+1)]);
  int right = (((c+1) >= static_cast<int>(cols_)) ? 1 : matrix_[r * cols_ + (c+1)]);
  int bottom_right = ((((r+1) >= static_cast<int>(rows_)) || ((c+1) >= static_cast<int>(cols_))) ? 1 : matrix_[(r+1) * cols_ + (c+1)]);
  int bottom = (((r+1) >= static_cast<int>(rows_)) ? 1 : matrix_[(r+1) * cols_ + c]);
  int bottom_left = (((r+1) >= static_cast<int>(rows_)) || ((c-1) < 0)) ? 1 : matrix_[(r+1) * cols_ + (c-1)];
  int left = (((c-1) < 0) ? 1 : matrix_[r * cols_ + (c-1)]);
  
  return top_left + top + top_right + right + bottom_right + bottom + bottom_left + left;
}


// PARSER
// ==================================================================
void Cave::CheckAndFixEndLine(std::string filepath) {
  FILE *fp = fopen(filepath.c_str(), "r+");
  if (fp == NULL) {
    throw std::invalid_argument("Failed to open file: " + filepath);
  }
  fseek(fp, -1, SEEK_END);
  char c = fgetc(fp);
  if (c != '\n') {
    fseek(fp, -1, SEEK_END);
    fputc('\n', fp);
  }
  fclose(fp);
}

void Cave::Parse(std::string filepath) {
  CheckAndFixEndLine(filepath);

  std::ifstream file(filepath);
  if (!file.is_open()) {
    throw std::invalid_argument("Failed to open file: " + filepath);
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
    throw std::invalid_argument("Failed to parse size of matrix");
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
