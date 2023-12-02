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
    int line_num = 0;
    size_t line_end = file_content.find('\n', pos);
    std::string line = file_content.substr(pos, line_end - pos);
    
    if (line_num == 0) {
      ParseSize(line);
    } else if (line_num > 0 && line_num < maze_->GetRows()) {
      ParseMatrixRight(line);
    } else {
      ParseMatrixBottom(line);
    }
    line_num++;
    pos = line_end + 1;
  }

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
  for (int i = 0; i < line.size(); i++) {
    int state = 0;
    MazeStatement statement;
    std::stringstream ss(line);
    ss >> state;
    switch (state) {
    case 0:
      statement = NO_BORDER;
      break;
    case 1:
      statement = RIGHT_BORDER;
      break;

    default:
      break;
    }

    matrix_right.push_back(statement);
  }
  maze_state_.(matrix_right);
}

void MazeParser::ParseMatrixBottom(std::string &line) {
  std::vector<MazeStatement> matrix_bottom;
  for (int i = 0; i < maze_->GetRows(); i++) {
    MazeStatement statement;
    std::stringstream ss(line);
    ss >> statement;
    matrix_bottom.push_back(statement);
  }
}


}  // namespace s21