#include "maze_parser.h"

namespace s21 {

void MazeParser::Parse() {
  std::ifstream file(filepath_);
  if (!file.is_open()) {
    throw std::invalid_argument("Failed to open file: " + filepath_);
  }

  Utils::CheckAndFixEndLine(filepath_);

  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string file_content = buffer.str();
  size_t pos = 0;
  size_t file_content_size = file_content.size();

  while (pos < file_content_size) {
    size_t line_end = file_content.find('\n', pos);
    std::string line = file_content.substr(pos, line_end - pos);
    if (current_line_ == 0) {
      ParseSize(line);
    } else if (current_line_ <= maze_->GetRows()) {
      ParseMatrixRight(line);
    } else if (current_line_ >= maze_->GetRows() + 2) {
      ParseMatrixBottom(line);
    }
    current_line_++;
    pos = line_end + 1;
  }
  MergeMatricies();
  file.close();
}

void MazeParser::SetFilePath(const std::string &filepath) {
  Reset();
  filepath_ = filepath;
}

void MazeParser::ParseSize(const std::string &line) {
  std::stringstream ss(line);
  int rows, cols;
  if (ss >> rows >> cols) {
    maze_->SetRows(rows);
    maze_->SetCols(cols);
  } else {
    throw std::invalid_argument("Failed to parse size of matrix: " + filepath_);
  }
}

void MazeParser::ParseMatrixRight(const std::string &line) {
  for (size_t i = 0; i < line.size(); i++) {
    Border border;
    if (line[i] == '0') {
      border = NO_BORDER;
      right_matrix_.push_back(border);
    } else if (line[i] == '1') {
      border = RIGHT_BORDER;
      right_matrix_.push_back(border);
    }
  }
}

void MazeParser::ParseMatrixBottom(const std::string &line) {
  for (size_t i = 0; i < line.size(); i++) {
    Border border;
    if (line[i] == '0') {
      border = NO_BORDER;
      bottom_matrix_.push_back(border);
    } else if (line[i] == '1') {
      border = BOTTOM_BORDER;
      bottom_matrix_.push_back(border);
    }
  }
}

void MazeParser::MergeMatricies() {
  if (right_matrix_.size() != bottom_matrix_.size()) {
    Reset();
    throw std::invalid_argument("Matrix size mismatch: " + filepath_);
  }

  if (right_matrix_.size() != (size_t)(maze_->GetCols() * maze_->GetRows())) {
    Reset();
    throw std::invalid_argument("First matrix size mismatch: " + filepath_);
  }

  if (bottom_matrix_.size() != (size_t)(maze_->GetCols() * maze_->GetRows())) {
    Reset();
    throw std::invalid_argument("Second matrix size mismatch: " + filepath_);
  }

  for (size_t i = 0; i < right_matrix_.size(); i++) {
    if (right_matrix_[i] == NO_BORDER && bottom_matrix_[i] == NO_BORDER) {
      maze_->Push(NO_BORDER);
    }
    if (right_matrix_[i] == NO_BORDER && bottom_matrix_[i] == BOTTOM_BORDER) {
      maze_->Push(BOTTOM_BORDER);
    }
    if (right_matrix_[i] == RIGHT_BORDER && bottom_matrix_[i] == NO_BORDER) {
      maze_->Push(RIGHT_BORDER);
    }
    if (right_matrix_[i] == RIGHT_BORDER &&
        bottom_matrix_[i] == BOTTOM_BORDER) {
      maze_->Push(BOTH_BORDER);
    }
  }
}

void MazeParser::Reset() {
  filepath_.clear();
  right_matrix_.clear();
  bottom_matrix_.clear();
  current_line_ = 0;
  maze_->Clear();
}

}  // namespace s21
