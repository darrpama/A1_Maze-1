#include <filesystem>

#include "../models/maze.h"
#include "../models/maze_parser.h"
#include "gtest/gtest.h"

using namespace s21;

// Positive test case for Parse function
TEST(MazeResolverTest, Parse_Positive) {
  s21::Maze maze(0, 0);
  s21::MazeParser parser(&maze);

  std::filesystem::path path = std::filesystem::current_path();
  std::string parent_path = path.parent_path();
  parent_path.append("/assets/maze.txt");

  parser.SetFilePath(parent_path);
  parser.Parse();

  size_t init_row = 0;
  size_t init_col = 0;
  size_t end_row = 0;
  size_t end_col = 3;

  std::vector<std::pair<size_t, size_t>> solution = maze.Resolve(
      std::make_pair(init_row, init_col), std::make_pair(end_row, end_col));
  for (size_t i = 0; i < solution.size(); i++) {
    std::cout << '[' << i << "]: " << solution[i].first << " "
              << solution[i].second << std::endl;
  }
}
