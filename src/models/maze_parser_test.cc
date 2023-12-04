#include "maze_parser.h"

#include "gtest/gtest.h"

using namespace s21;

// Positive test case for ParseSize function
TEST(MazeParserTest, ParseSize_Positive) {
  s21::Maze maze(0, 0);
  s21::MazeParser parser(&maze);

  parser.SetFilePath("/Users/darrpama/projects/A1_Maze-1/src/assets/maze.txt");
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
}

// Positive test case for Parse function
TEST(MazeParserTest, Parse_Positive) {
  s21::Maze maze(0, 0);
  s21::MazeParser parser(&maze);

  parser.SetFilePath(
      "/Users/darrpama/projects/A1_Maze-1/src/assets/maze_small.txt");
  parser.Parse();

  EXPECT_EQ(maze.GetRows(), 3);
  EXPECT_EQ(maze.GetCols(), 3);

  std::vector<Border> expected_mat = {
      NO_BORDER,    BOTTOM_BORDER, RIGHT_BORDER,  BOTTOM_BORDER, BOTH_BORDER,
      RIGHT_BORDER, BOTH_BORDER,   BOTTOM_BORDER, BOTH_BORDER};

  std::vector<Border> mat = maze.GetMatrix();
  EXPECT_EQ(mat.size(), 9);

  for (int i = 0; i < mat.size(); i++) {
    EXPECT_EQ(mat[i], expected_mat[i]);
  }
}

// Negative test case for Parse function
TEST(MazeParserTest, Parse_Negative_No_File) {
  s21::Maze maze(0, 0);
  s21::MazeParser parser(&maze);

  parser.SetFilePath(
      "/Users/darrpama/projects/A1_Maze-1/src/assets/maze_no_exist.txt");
  EXPECT_ANY_THROW(parser.Parse());

  EXPECT_EQ(maze.GetRows(), 0);
  EXPECT_EQ(maze.GetCols(), 0);

  std::vector<Border> mat = maze.GetMatrix();
  EXPECT_EQ(mat.size(), 0);
}

// Negative test case for Parse function
TEST(MazeParserTest, Parse_Negative_Cols_1_Test) {
  s21::Maze maze(0, 0);
  s21::MazeParser parser(&maze);

  parser.SetFilePath(
      "/Users/darrpama/projects/A1_Maze-1/src/assets/maze_non_eq_cols_1_mat.txt");
  EXPECT_ANY_THROW(parser.Parse());

  EXPECT_EQ(maze.GetRows(), 0);
  EXPECT_EQ(maze.GetCols(), 0);

  std::vector<Border> mat = maze.GetMatrix();
  EXPECT_EQ(mat.size(), 0);
}

// Negative test case for Parse function
TEST(MazeParserTest, Parse_Negative_Cols_2_Test) {
  s21::Maze maze(0, 0);
  s21::MazeParser parser(&maze);

  parser.SetFilePath(
      "/Users/darrpama/projects/A1_Maze-1/src/assets/maze_non_eq_cols_2_mat.txt");
  EXPECT_ANY_THROW(parser.Parse());

  EXPECT_EQ(maze.GetRows(), 0);
  EXPECT_EQ(maze.GetCols(), 0);

  std::vector<Border> mat = maze.GetMatrix();
  EXPECT_EQ(mat.size(), 0);
}

// Negative test case for Parse function
TEST(MazeParserTest, Parse_Negative_Rows_1_Test) {
  s21::Maze maze(0, 0);
  s21::MazeParser parser(&maze);

  parser.SetFilePath(
      "/Users/darrpama/projects/A1_Maze-1/src/assets/maze_non_eq_rows_1_mat.txt");
  EXPECT_NO_THROW(parser.Parse());

  EXPECT_EQ(maze.GetRows(), 3);
  EXPECT_EQ(maze.GetCols(), 3);

  std::vector<Border> mat = maze.GetMatrix();
  EXPECT_EQ(mat.size(), 9);
}

// Negative test case for Parse function
TEST(MazeParserTest, Parse_Negative_Rows_2_Test) {
  s21::Maze maze(0, 0);
  s21::MazeParser parser(&maze);

  parser.SetFilePath(
      "/Users/darrpama/projects/A1_Maze-1/src/assets/maze_non_eq_rows_2_mat.txt");
  EXPECT_ANY_THROW(parser.Parse());

  EXPECT_EQ(maze.GetRows(), 0);
  EXPECT_EQ(maze.GetCols(), 0);

  std::vector<Border> mat = maze.GetMatrix();
  EXPECT_EQ(mat.size(), 0);
}

// Negative test case for Parse function
TEST(MazeParserTest, Parse_1_Matrix_Test) {
  s21::Maze maze(0, 0);
  s21::MazeParser parser(&maze);

  parser.SetFilePath(
      "/Users/darrpama/projects/A1_Maze-1/src/assets/maze_1_mat_wrong.txt");
  EXPECT_ANY_THROW(parser.Parse());

  EXPECT_EQ(maze.GetRows(), 0);
  EXPECT_EQ(maze.GetCols(), 0);

  std::vector<Border> mat = maze.GetMatrix();
  EXPECT_EQ(mat.size(), 0);
}

// Negative test case for Parse function
TEST(MazeParserTest, Parse_2_Matrix_Test) {
  s21::Maze maze(0, 0);
  s21::MazeParser parser(&maze);

  parser.SetFilePath(
      "/Users/darrpama/projects/A1_Maze-1/src/assets/maze_2_mat_wrong.txt");
  EXPECT_ANY_THROW(parser.Parse());

  EXPECT_EQ(maze.GetRows(), 0);
  EXPECT_EQ(maze.GetCols(), 0);

  std::vector<Border> mat = maze.GetMatrix();
  EXPECT_EQ(mat.size(), 0);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}