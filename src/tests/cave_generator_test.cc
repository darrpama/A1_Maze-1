#include "../models/cave/cave.h"

#include <filesystem>

#include <gtest/gtest.h>

TEST(CaveGenerator, test1) {
  int expected_rows = 10;
  int expected_cols = 10;
  std::vector<unsigned> expected_matrix = {
    1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 
    0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 
    0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 
    0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 
    0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 
    0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 
    1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 
    0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 
    1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 
    0, 1, 1, 0, 0, 1, 1, 0, 0, 0 
  };

  std::filesystem::path path = std::filesystem::current_path();
  std::string filepath = path.parent_path();
  filepath.append("/src/assets/cave10x10.txt");

  s21::Cave cave(0,0);
  cave.Parse(filepath);

  EXPECT_EQ(cave.GetRows(), expected_rows);
  EXPECT_EQ(cave.GetCols(), expected_cols);
}
