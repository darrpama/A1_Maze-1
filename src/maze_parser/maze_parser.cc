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
  }

  std::getline(file, line);
  ParseSize(line);
  ParseMatrixRight(line);
  ParseMatrixBottom(line);
  file.close();
}

void MazeParser::SetFilePath(const std::string &filepath) {
  filepath_ = filepath;
}

void MazeParser::ParseSize(std::string &line) {
  std::stringstream ss(line);
  int rows, cols;
  ss >> rows >> cols;
  maze_->SetRows(rows);
  maze_->SetCols(cols);
}

void MazeParser::ParseMatrixRight(std::string &line) {
  std::vector<MazeStatement> matrix_right;
  for (int i = 0; i < maze_->GetRows(); i++) {
    MazeStatement statement;
    std::stringstream ss(line);
    ss >> statement;
    matrix_right.push_back(statement);
  }
  maze_->SetMazeStatement(matrix_right);
}

void MazeParser::ParseMatrixBottom(std::string &) {
  std::vector<MazeStatement> matrix_bottom;
  for (int i = 0; i < maze_->GetCols(); i++) {
    MazeStatement statement;
    std::stringstream ss(line);
    ss >> statement;
    matrix_bottom.push_back(statement);
  }
  maze_->SetMazeStatement(matrix_bottom);
}


}  // namespace s21