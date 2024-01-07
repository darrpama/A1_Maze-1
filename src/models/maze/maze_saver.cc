#include "maze_saver.h"

namespace s21 {
MazeSaver::MazeSaver(Maze* maze) : maze_(maze){};

void MazeSaver::Save() {
  std::ofstream file(filepath_);
  if (!file.is_open()) {
    throw std::invalid_argument("Failed to open file: " + filepath_);
  }

  UnmergeMatricies();
  WriteSize(file);
  WriteMatrixRight(file);
  WriteMatrixBottom(file);
  file.close();
}

void MazeSaver::SetFilePath(const std::string& filepath) {
  Reset();
  filepath_ = filepath;
}

void MazeSaver::SetMaze(Maze* maze) { maze_ = maze; }

void MazeSaver::UnmergeMatricies() {
  const auto& matrix = maze_->GetMatrix();
  right_matrix_.reserve(matrix.size());
  bottom_matrix_.reserve(matrix.size());

  for (size_t cell = 0; cell < matrix.size(); cell++) {
    if (matrix[cell] == NO_BORDER) {
      right_matrix_.push_back(NO_BORDER);
      bottom_matrix_.push_back(NO_BORDER);
    } else if (matrix[cell] == RIGHT_BORDER) {
      right_matrix_.push_back(RIGHT_BORDER);
      bottom_matrix_.push_back(NO_BORDER);
    } else if (matrix[cell] == BOTTOM_BORDER) {
      right_matrix_.push_back(NO_BORDER);
      bottom_matrix_.push_back(BOTTOM_BORDER);
    } else if (matrix[cell] == BOTH_BORDER) {
      right_matrix_.push_back(RIGHT_BORDER);
      bottom_matrix_.push_back(BOTTOM_BORDER);
    }
  }
}

void MazeSaver::WriteSize(std::ofstream& file) {
  file << maze_->GetRows() << " " << maze_->GetCols() << std::endl;
}

void MazeSaver::WriteMatrixRight(std::ofstream& file) {
  int i = 1;
  for (const auto& cell : right_matrix_) {
    if (cell == NO_BORDER) {
      file << 0;
    } else if (cell == RIGHT_BORDER) {
      file << 1;
    }
    if (i % maze_->GetCols()) {
      file << " ";
    } else {
      file << std::endl;
    }
    i++;
  }
  file << std::endl;
}

void MazeSaver::WriteMatrixBottom(std::ofstream& file) {
  int i = 1;
  for (const auto& cell : bottom_matrix_) {
    if (cell == NO_BORDER) {
      file << 0;
    } else if (cell == BOTTOM_BORDER) {
      file << 1;
    }
    if (i % maze_->GetCols()) {
      file << " ";
    } else {
      file << std::endl;
    }
    i++;
  }
}

void MazeSaver::Reset() {
  filepath_.clear();
  right_matrix_.clear();
  bottom_matrix_.clear();
}

}  // namespace s21