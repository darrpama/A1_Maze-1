#include "maze_parser.h"

namespace s21 {


void MazeParser::Parse() {
  std::ifstream file(filepath_);
  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << filepath_ << std::endl;
    return;
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string file_content = buffer.str();
  size_t pos = 0;
  size_t file_content_size = file_content.size();

  while (pos < file_content_size) {
    size_t line_end = file_content.find('\n', pos);
    std::string line = file_content.substr(pos, line_end - pos);
    try {
      // std::cout << "current_line = " << current_line_ << std::endl;
      if (current_line_== 0) {
        ParseSize(line);
      } else if (current_line_ > 0 && current_line_ <= maze_->GetRows()) {
        ParseMatrixRight(line);
      } else if (current_line_ >= maze_->GetRows() + 2)  {
        ParseMatrixBottom(line);
      }
      current_line_++;
      pos = line_end + 1;
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
     
  }

  MergeMatricies();
  file.close();
}

void MazeParser::SetFilePath(const std::string &filepath) {
  filepath_ = filepath;
}

void MazeParser::ParseSize(std::string &line) {
  std::stringstream ss(line);
  int rows, cols;
  if (ss >> rows >> cols) {
    maze_->SetRows(rows);
    maze_->SetCols(cols);
  } else {
    std::cerr << "Failed to parse size of matrix: " << filepath_ << std::endl;
    return;
  }
}

void MazeParser::ParseMatrixRight(std::string &line) {
  // std::cout << "right: " << line << std::endl;
  for (int i = 0; i < line.size(); i++) {
    Border border;
    switch (line[i]) {
    case '0':
      border = NO_BORDER;
      right_matrix_.push_back(border);
      break;
    case '1':
      border = RIGHT_BORDER;
      right_matrix_.push_back(border);
      break;
    default:
      break;
    }
  }
}

void MazeParser::ParseMatrixBottom(std::string &line) {
  // std::cout << "bottom: " <<line << std::endl;
  for (int i = 0; i < line.size(); i++) {
    Border border;
    switch (line[i]) {
    case '0':
      border = NO_BORDER;
      bottom_matrix_.push_back(border);
      break;
    case '1':
      border = BOTTOM_BORDER;
      bottom_matrix_.push_back(border);
      break;
    default:
      break;
    }
  }
}

void MazeParser::MergeMatricies() {
  std::cout << "matrix_size before merge: " << right_matrix_.size() << std::endl;
  for (int i = 0; i < right_matrix_.size(); i++) {
    switch (right_matrix_[i])
    {
    case NO_BORDER:
      if (bottom_matrix_[i] == NO_BORDER) {
        maze_->Push(NO_BORDER);
      } else if (bottom_matrix_[i] == BOTTOM_BORDER) {
        maze_->Push(BOTTOM_BORDER);
      }
      break;
    case RIGHT_BORDER:
      if (bottom_matrix_[i] == NO_BORDER) {
        maze_->Push(RIGHT_BORDER);
      } else if (bottom_matrix_[i] == BOTTOM_BORDER) {
        maze_->Push(BOTH_BORDER);
      }
      break;

    default:
      break;
    }
  }
}

}  // namespace s21