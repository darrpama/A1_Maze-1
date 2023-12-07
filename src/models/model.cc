#include "model.h"

namespace s21 {

void Model::UploadMaze(std::string filepath) {
  maze_parser_->SetFilePath(filepath);
  maze_parser_->Parse();
}

}  // namespace s21
