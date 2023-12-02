#include "maze_parser.h"
#include "gtest/gtest.h"

using namespace s21;

// Positive test case for ParseSize function
TEST(MazeParserTest, ParseSize_Positive) {
  s21::Maze maze(0, 0);
  s21::MazeParser parser(&maze);

  parser.SetFilePath("/Users/darrpama/projects/A1_Maze-1/src/assets/maze.txt");
  parser.Parse();
  
  EXPECT_EQ(maze.GetRows(), 10);
  EXPECT_EQ(maze.GetCols(), 10);
  std::vector<Border> mat = maze.GetMatrix();
  // EXPECT_EQ(mat.size(), 6);
}

// Positive test case for Parse function
TEST(MazeParserTest, Parse_Positive) {
  s21::Maze maze(0, 0);
  s21::MazeParser parser(&maze);

  parser.SetFilePath("/Users/darrpama/projects/A1_Maze-1/src/assets/maze_small.txt");
  parser.Parse();
  
  EXPECT_EQ(maze.GetRows(), 3);
  EXPECT_EQ(maze.GetCols(), 3);

  std::vector<Border> mat = maze.GetMatrix();
  EXPECT_EQ(mat.size(), 9);

  // for (int i = 0; i < mat.size(); i++) {
  //   std::cout << mat[i] << " ";
  // }
  // std::cout << std::endl;
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}