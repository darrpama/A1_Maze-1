#include "../models/cave/cave_generator.h"

#include <gtest/gtest.h>

TEST(CaveGenerator, test1) {
  s21::CaveGenerator generator;
  s21::Cave cave = generator.Generate(20, 20, 0.5);

  EXPECT_EQ(cave.GetRows(), 20);
  EXPECT_EQ(cave.GetCols(), 20);
}
