#include <filesystem>

#include "../models/maze/maze.h"
#include "../models/maze/maze_parser.h"
#include "gtest/gtest.h"

using namespace s21;

// Positive test case for resolve function
TEST(MazeResolverTest, Resolve_Positive) {
  s21::Maze maze(0, 0);
  s21::MazeParser parser(&maze);

  std::filesystem::path path = std::filesystem::current_path();
  std::string parent_path = path.parent_path();
  parent_path.append("/src/assets/maze.txt");

  parser.SetFilePath(parent_path);
  parser.Parse();

  size_t init_row = 0;
  size_t init_col = 0;
  size_t end_row = 0;
  size_t end_col = 3;

  std::vector<s21::Vector2D> solution = maze.Resolve(
      s21::Vector2D(init_row, init_col), s21::Vector2D(end_row, end_col));

  std::vector<s21::Vector2D> correct_solution{
      {0, 3}, {1, 3}, {2, 3}, {2, 4}, {2, 5}, {3, 5}, {3, 4}, {4, 4}, {4, 3},
      {3, 3}, {3, 2}, {3, 1}, {2, 1}, {2, 2}, {1, 2}, {0, 2}, {0, 1}, {0, 0}};

  for (size_t i = 0; i < solution.size(); i++) {
    EXPECT_EQ(solution[i].x_, correct_solution[i].x_);
    EXPECT_EQ(solution[i].y_, correct_solution[i].y_);
  }
}
