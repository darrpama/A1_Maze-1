#include "../models/maze/maze_parser.h"

#include <filesystem>

#include "gtest/gtest.h"

using namespace s21;

// Positive test case for ParseSize function
TEST(MazeParserTest, ParseSize_Positive) {
  s21::Maze maze(0, 0);
  s21::MazeParser parser(&maze);

  std::filesystem::path path = std::filesystem::current_path();
  std::string parent_path = path.parent_path();
  parent_path.append("/src/assets/maze.txt");

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
  EXPECT_EQ(mat.size(), (size_t)100);

  for (size_t i = 0; i < mat.size(); i++) {
    EXPECT_EQ(mat[i], expected_mat[i]);
  }
}

// Positive test case for Parse function
TEST(MazeParserTest, Parse_Positive) {
  s21::Maze maze(0, 0);
  s21::MazeParser parser(&maze);

  std::filesystem::path path = std::filesystem::current_path();
  std::string parent_path = path.parent_path();
  parent_path.append("/src/assets/maze_small.txt");

  parser.SetFilePath(parent_path);
  parser.Parse();

  EXPECT_EQ(maze.GetRows(), 3);
  EXPECT_EQ(maze.GetCols(), 3);

  std::vector<Border> expected_mat = {
      NO_BORDER,    BOTTOM_BORDER, RIGHT_BORDER,  BOTTOM_BORDER, BOTH_BORDER,
      RIGHT_BORDER, BOTH_BORDER,   BOTTOM_BORDER, BOTH_BORDER};

  std::vector<Border> mat = maze.GetMatrix();
  EXPECT_EQ(mat.size(), (size_t)9);

  for (size_t i = 0; i < mat.size(); i++) {
    EXPECT_EQ(mat[i], expected_mat[i]);
  }
}

// Negative test case for Parse function
TEST(MazeParserTest, Parse_Negative_No_File) {
  s21::Maze maze(0, 0);
  s21::MazeParser parser(&maze);

  std::filesystem::path path = std::filesystem::current_path();
  std::string parent_path = path.parent_path();
  parent_path.append("/src/assets/maze_no_exist.txt");

  parser.SetFilePath(parent_path);

  EXPECT_ANY_THROW(parser.Parse());

  EXPECT_EQ(maze.GetRows(), 0);
  EXPECT_EQ(maze.GetCols(), 0);

  std::vector<Border> mat = maze.GetMatrix();
  EXPECT_EQ(mat.size(), (size_t)0);
}

// Negative test case for Parse function
TEST(MazeParserTest, Parse_Negative_Cols_1_Test) {
  s21::Maze maze(0, 0);
  s21::MazeParser parser(&maze);

  std::filesystem::path path = std::filesystem::current_path();
  std::string parent_path = path.parent_path();
  parent_path.append("/src/assets/maze_non_eq_cols_1_mat.txt");

  parser.SetFilePath(parent_path);

  EXPECT_ANY_THROW(parser.Parse());

  EXPECT_EQ(maze.GetRows(), 0);
  EXPECT_EQ(maze.GetCols(), 0);

  std::vector<Border> mat = maze.GetMatrix();
  EXPECT_EQ(mat.size(), (size_t)0);
}

// Negative test case for Parse function
TEST(MazeParserTest, Parse_Negative_Cols_2_Test) {
  s21::Maze maze(0, 0);
  s21::MazeParser parser(&maze);

  std::filesystem::path path = std::filesystem::current_path();
  std::string parent_path = path.parent_path();
  parent_path.append("/src/assets/maze_non_eq_cols_2_mat.txt");

  parser.SetFilePath(parent_path);

  EXPECT_ANY_THROW(parser.Parse());

  EXPECT_EQ(maze.GetRows(), 0);
  EXPECT_EQ(maze.GetCols(), 0);

  std::vector<Border> mat = maze.GetMatrix();
  EXPECT_EQ(mat.size(), (size_t)0);
}

// Negative test case for Parse function
TEST(MazeParserTest, Parse_Negative_Cols_3_Test) {
  s21::Maze maze(0, 0);
  s21::MazeParser parser(&maze);

  std::filesystem::path path = std::filesystem::current_path();
  std::string parent_path = path.parent_path();
  parent_path.append("/src/assets/maze_non_eq_cols_1_mat_2.txt");

  parser.SetFilePath(parent_path);

  EXPECT_ANY_THROW(parser.Parse());

  EXPECT_EQ(maze.GetRows(), 0);
  EXPECT_EQ(maze.GetCols(), 0);

  std::vector<Border> mat = maze.GetMatrix();
  EXPECT_EQ(mat.size(), (size_t)0);
}

// Negative test case for Parse function
TEST(MazeParserTest, Parse_Negative_Cols_4_Test) {
  s21::Maze maze(0, 0);
  s21::MazeParser parser(&maze);

  std::filesystem::path path = std::filesystem::current_path();
  std::string parent_path = path.parent_path();
  parent_path.append("/src/assets/maze_non_eq_cols_2_mat_2.txt");

  parser.SetFilePath(parent_path);

  EXPECT_ANY_THROW(parser.Parse());

  EXPECT_EQ(maze.GetRows(), 0);
  EXPECT_EQ(maze.GetCols(), 0);

  std::vector<Border> mat = maze.GetMatrix();
  EXPECT_EQ(mat.size(), (size_t)0);
}

// Negative test case for Parse function
TEST(MazeParserTest, Parse_Negative_Rows_1_Test) {
  s21::Maze maze(0, 0);
  s21::MazeParser parser(&maze);

  std::filesystem::path path = std::filesystem::current_path();
  std::string parent_path = path.parent_path();
  parent_path.append("/src/assets/maze_non_eq_rows_1_mat.txt");

  parser.SetFilePath(parent_path);

  EXPECT_NO_THROW(parser.Parse());

  EXPECT_EQ(maze.GetRows(), 3);
  EXPECT_EQ(maze.GetCols(), 3);

  std::vector<Border> mat = maze.GetMatrix();
  EXPECT_EQ(mat.size(), (size_t)9);
}

// Negative test case for Parse function
TEST(MazeParserTest, Parse_Negative_Rows_2_Test) {
  s21::Maze maze(0, 0);
  s21::MazeParser parser(&maze);

  std::filesystem::path path = std::filesystem::current_path();
  std::string parent_path = path.parent_path();
  parent_path.append("/src/assets/maze_non_eq_rows_2_mat.txt");

  parser.SetFilePath(parent_path);

  EXPECT_ANY_THROW(parser.Parse());

  EXPECT_EQ(maze.GetRows(), 0);
  EXPECT_EQ(maze.GetCols(), 0);

  std::vector<Border> mat = maze.GetMatrix();
  EXPECT_EQ(mat.size(), (size_t)0);
}

// Negative test case for Parse function
TEST(MazeParserTest, Parse_Negative_Rows_3_Test) {
  s21::Maze maze(0, 0);
  s21::MazeParser parser(&maze);

  std::filesystem::path path = std::filesystem::current_path();
  std::string parent_path = path.parent_path();
  parent_path.append("/src/assets/maze_non_eq_rows_1_mat_2.txt");

  parser.SetFilePath(parent_path);

  EXPECT_ANY_THROW(parser.Parse());

  EXPECT_EQ(maze.GetRows(), 0);
  EXPECT_EQ(maze.GetCols(), 0);

  std::vector<Border> mat = maze.GetMatrix();
  EXPECT_EQ(mat.size(), (size_t)0);
}

// Negative test case for Parse function
TEST(MazeParserTest, Parse_Negative_Rows_4_Test) {
  s21::Maze maze(0, 0);
  s21::MazeParser parser(&maze);

  std::filesystem::path path = std::filesystem::current_path();
  std::string parent_path = path.parent_path();
  parent_path.append("/src/assets/maze_non_eq_rows_2_mat_2.txt");

  parser.SetFilePath(parent_path);

  EXPECT_ANY_THROW(parser.Parse());

  EXPECT_EQ(maze.GetRows(), 0);
  EXPECT_EQ(maze.GetCols(), 0);

  std::vector<Border> mat = maze.GetMatrix();
  EXPECT_EQ(mat.size(), (size_t)0);
}

// Negative test case for Parse function
TEST(MazeParserTest, Parse_1_Matrix_Test) {
  s21::Maze maze(0, 0);
  s21::MazeParser parser(&maze);

  std::filesystem::path path = std::filesystem::current_path();
  std::string parent_path = path.parent_path();
  parent_path.append("/src/assets/maze_1_mat_wrong.txt");

  parser.SetFilePath(parent_path);

  EXPECT_ANY_THROW(parser.Parse());

  EXPECT_EQ(maze.GetRows(), 0);
  EXPECT_EQ(maze.GetCols(), 0);

  std::vector<Border> mat = maze.GetMatrix();
  EXPECT_EQ(mat.size(), (size_t)0);
}

// Negative test case for Parse function
TEST(MazeParserTest, Parse_2_Matrix_Test) {
  s21::Maze maze(0, 0);
  s21::MazeParser parser(&maze);

  std::filesystem::path path = std::filesystem::current_path();
  std::string parent_path = path.parent_path();
  parent_path.append("/src/assets/maze_2_mat_wrong.txt");

  parser.SetFilePath(parent_path);

  EXPECT_ANY_THROW(parser.Parse());

  EXPECT_EQ(maze.GetRows(), 0);
  EXPECT_EQ(maze.GetCols(), 0);

  std::vector<Border> mat = maze.GetMatrix();
  EXPECT_EQ(mat.size(), (size_t)0);
}

// Negative test case for Parse function
TEST(MazeParserTest, Parse_Size_Rows_Test) {
  s21::Maze maze(0, 0);
  s21::MazeParser parser(&maze);

  std::filesystem::path path = std::filesystem::current_path();
  std::string parent_path = path.parent_path();
  parent_path.append("/src/assets/maze_rows_wrong.txt");

  parser.SetFilePath(parent_path);

  EXPECT_ANY_THROW(parser.Parse());

  EXPECT_EQ(maze.GetRows(), 0);
  EXPECT_EQ(maze.GetCols(), 0);

  std::vector<Border> mat = maze.GetMatrix();
  EXPECT_EQ(mat.size(), (size_t)0);
}

// Negative test case for Parse function
TEST(MazeParserTest, Parse_Size_Cols_Test) {
  s21::Maze maze(0, 0);
  s21::MazeParser parser(&maze);

  std::filesystem::path path = std::filesystem::current_path();
  std::string parent_path = path.parent_path();
  parent_path.append("/src/assets/maze_cols_wrong.txt");

  parser.SetFilePath(parent_path);

  EXPECT_ANY_THROW(parser.Parse());

  EXPECT_EQ(maze.GetRows(), 0);
  EXPECT_EQ(maze.GetCols(), 0);

  std::vector<Border> mat = maze.GetMatrix();
  EXPECT_EQ(mat.size(), (size_t)0);
}
