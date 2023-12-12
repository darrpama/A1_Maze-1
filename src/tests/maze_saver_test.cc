#include "../models/maze_parser.h"
#include "../models/maze_saver.h"

#include "gtest/gtest.h"

#include <filesystem>

using namespace s21;

// Positive test case for ParseSize function
TEST(MazeParserTest, MazeSaver_Positive) {
  s21::Maze maze(0, 0);
  s21::MazeParser parser(&maze);

  std::filesystem::path path = std::filesystem::current_path();
  std::string parent_path = path.parent_path();
  parent_path.append("/assets/maze.txt");
  std::string parent_path_to_save = path.parent_path();
  parent_path_to_save.append("/assets/saved_maze.txt");

  parser.SetFilePath(parent_path);
  parser.Parse();

  std::vector<Border> expected_mat = {
      NO_BORDER,     BOTTOM_BORDER, RIGHT_BORDER,  NO_BORDER,     NO_BORDER,
      BOTTOM_BORDER, BOTTOM_BORDER, BOTH_BORDER,   NO_BORDER,     RIGHT_BORDER,
      BOTTOM_BORDER, BOTH_BORDER,   RIGHT_BORDER,  RIGHT_BORDER,  BOTTOM_BORDER,
      BOTTOM_BORDER, BOTTOM_BORDER, RIGHT_BORDER,  RIGHT_BORDER,  RIGHT_BORDER,
      RIGHT_BORDER,  NO_BORDER,     BOTH_BORDER,   BOTTOM_BORDER, BOTTOM_BORDER,
      RIGHT_BORDER,  RIGHT_BORDER,  RIGHT_BORDER,  RIGHT_BORDER,  RIGHT_BORDER,
      RIGHT_BORDER,  BOTTOM_BORDER, BOTTOM_BORDER, RIGHT_BORDER,  NO_BORDER,
      BOTTOM_BORDER, RIGHT_BORDER,  NO_BORDER,     BOTH_BORDER,   RIGHT_BORDER,
      BOTTOM_BORDER, NO_BORDER,     BOTH_BORDER,   BOTTOM_BORDER, BOTH_BORDER,
      NO_BORDER,     BOTH_BORDER,   BOTTOM_BORDER, BOTH_BORDER,   RIGHT_BORDER,
      RIGHT_BORDER,  BOTTOM_BORDER, BOTTOM_BORDER, BOTTOM_BORDER, NO_BORDER,
      BOTH_BORDER,   RIGHT_BORDER,  NO_BORDER,     RIGHT_BORDER,  RIGHT_BORDER,
      BOTTOM_BORDER, BOTTOM_BORDER, NO_BORDER,     BOTH_BORDER,   RIGHT_BORDER,
      NO_BORDER,     BOTTOM_BORDER, RIGHT_BORDER,  BOTTOM_BORDER, BOTH_BORDER,
      NO_BORDER,     BOTTOM_BORDER, BOTTOM_BORDER, BOTTOM_BORDER, BOTH_BORDER,
      NO_BORDER,     RIGHT_BORDER,  RIGHT_BORDER,  BOTTOM_BORDER, RIGHT_BORDER,
      BOTH_BORDER,   NO_BORDER,     BOTTOM_BORDER, NO_BORDER,     RIGHT_BORDER,
      RIGHT_BORDER,  RIGHT_BORDER,  BOTTOM_BORDER, BOTTOM_BORDER, BOTH_BORDER,
      BOTTOM_BORDER, BOTH_BORDER,   BOTTOM_BORDER, BOTH_BORDER,   BOTTOM_BORDER,
      BOTH_BORDER,   BOTTOM_BORDER, BOTTOM_BORDER, BOTTOM_BORDER, BOTH_BORDER};

  EXPECT_EQ(maze.GetRows(), 10);
  EXPECT_EQ(maze.GetCols(), 10);
  std::vector<Border> mat = maze.GetMatrix();
  EXPECT_EQ(mat.size(), 100);

  for (int i = 0; i < mat.size(); i++) {
    EXPECT_EQ(mat[i], expected_mat[i]);
  }

  MazeSaver saver(maze);
  saver.SetFilePath(parent_path_to_save);
  EXPECT_NO_THROW(saver.Save());

  parser.SetFilePath(parent_path_to_save);
  EXPECT_NO_THROW(parser.Parse());

  EXPECT_EQ(maze.GetRows(), 10);
  EXPECT_EQ(maze.GetCols(), 10);
  std::vector<Border> mat2 = maze.GetMatrix();
  EXPECT_EQ(mat2.size(), 100);

  for (int i = 0; i < mat2.size(); i++) {
    EXPECT_EQ(mat2[i], expected_mat[i]);
  }

}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}