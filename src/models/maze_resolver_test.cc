#include "maze_parser.h"
#include "maze_resolver.h"

#include "gtest/gtest.h"

#include <filesystem>

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

  MazeResolver resolver(maze);
  std::vector<std::pair<size_t, size_t>> solution = resolver.Resolve(std::make_pair(init_row, init_col), std::make_pair(end_row, end_col));
  for (size_t i = 0; i < solution.size(); i++) {
    std::cout << '[' << i << "]: " << solution[i].first << " " << solution[i].second << std::endl;
  }
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}