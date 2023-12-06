#include "maze_saver.h"

namespace s21 {

void MazeSaver::Save() {
  std::ifstream file(filepath_);
  if (!file.is_open()) {
    throw std::invalid_argument("Failed to open file: " + filepath_);
  }

  UnmergeMatricies();
  WriteSize();
  WriteMatrixRight();
  WriteMatrixBottom();
  file.close();
}

void MazeSaver::SetFilePath(const std::string &filepath) {
  Reset();
  filepath_ = filepath;
}

void MazeSaver::UnmergeMatricies() {
  for (size_t cell = 0; cell < maze_->GetMatrix().size(); cell++) {
    if (maze_->GetMatrix()[cell] == NO_BORDER) {
      right_matrix_.push_back(NO_BORDER);
      bottom_matrix_.push_back(NO_BORDER);
    } else if (maze_->GetMatrix()[cell] == RIGHT_BORDER) {
      right_matrix_.push_back(RIGHT_BORDER);
      bottom_matrix_.push_back(NO_BORDER);
    } else if (maze_->GetMatrix()[cell] == BOTTOM_BORDER) {
      right_matrix_.push_back(NO_BORDER);
      bottom_matrix_.push_back(BOTTOM_BORDER);
    } else if (maze_->GetMatrix()[cell] == BOTH_BORDER) {
      right_matrix_.push_back(RIGHT_BORDER);
      bottom_matrix_.push_back(BOTTOM_BORDER);
    }
  }
}


void MazeSaver::WriteSize() {
}

void MazeSaver::WriteMatrixRight() {
}

void MazeSaver::WriteMatrixBottom() {
}


void MazeSaver::Reset() {
  filepath_.clear();
  right_matrix_.clear();
  bottom_matrix_.clear();
}

}  // namespace s21