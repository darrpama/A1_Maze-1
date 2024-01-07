#include "../models/cave/cave.h"

#include <gtest/gtest.h>

#include <filesystem>

bool CompareMatrices(const std::vector<unsigned> &m1,
                     const std::vector<unsigned> &m2) {
  if (m1.size() != m2.size()) {
    return false;  // LCOV_EXCL_LINE
  }

  for (size_t i = 0; i < m1.size(); i++) {
    if (m1[i] != m2[i]) {
      return false;  // LCOV_EXCL_LINE
    }
  }

  return true;
}

TEST(Cave, test1) {
  int expected_rows = 10;
  int expected_cols = 10;
  std::vector<unsigned> expected_matrix = {
      1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1,
      0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
      0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0,
      1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
      1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0};

  std::vector<unsigned> expected_render_matrix = {
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1,
      1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

  std::filesystem::path path = std::filesystem::current_path();
  std::string filepath = path.parent_path().string();
  filepath.append("/src/assets/cave10x10.txt");

  s21::Cave cave;
  cave.ParseFromFile(filepath);

  EXPECT_EQ(cave.GetRows(), expected_rows);
  EXPECT_EQ(cave.GetCols(), expected_cols);
  EXPECT_TRUE(CompareMatrices(expected_matrix, cave.GetMatrix()));

  bool done = false;
  while (!done) {
    done = cave.StepRender(3, 4);
  }

  EXPECT_TRUE(CompareMatrices(cave.GetMatrix(), expected_render_matrix));
}

TEST(Cave, test2) {
  s21::Cave cave;
  cave.Generate(5, 5, 0.5);
  EXPECT_EQ(cave.GetRows(), 5);
  EXPECT_EQ(cave.GetCols(), 5);
}