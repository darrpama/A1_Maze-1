#include "cave_parser.h"

namespace s21 {

void CaveParser::CheckAndFixEndLine() {
  const char *filepath = filepath_.c_str();
  FILE *fp = fopen(filepath, "r+");
  if (fp == NULL) {
    throw std::invalid_argument("Failed to open file: " + filepath_);
  }
  fseek(fp, -1, SEEK_END);
  char c = fgetc(fp);
  if (c != '\n') {
    fseek(fp, -1, SEEK_END);
    fputc('\n', fp);
  }
  fclose(fp);
}

void CaveParser::Parse() {
  CheckAndFixEndLine();

  std::ifstream file(filepath_);
  if (!file.is_open()) {
    throw std::invalid_argument("Failed to open file: " + filepath_);
  }

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
    } else {
      ParseMatrix(line);
    }
    current_line_++;
    pos = line_end + 1;
  }

  file.close();
}

void CaveParser::SetFilePath(const std::string &filepath) {
  Reset();
  filepath_ = filepath;
}

void CaveParser::ParseSize(const std::string &line) {
  std::stringstream ss(line);
  int rows, cols;
  if (ss >> rows >> cols) {
    cave_->SetRows(rows);
    cave_->SetCols(cols);
  } else {
    throw std::invalid_argument("Failed to parse size of matrix: " + filepath_);
  }
}

void CaveParser::ParseMatrix(const std::string &line) {
  for (size_t i = 0; i < line.size(); i++) {
    if (line[i] == '0') {
      cave_->Push(0);
    } else if (line[i] == '1') {
      cave_->Push(1);
    }
  }
}

void CaveParser::Reset() {
  filepath_.clear();
  matrix_.clear();
  current_line_ = 0;
  cave_->Clear();
}

}  // namespace s21