#include "../models/maze_generator.h"

#include <gtest/gtest.h>

using namespace s21;

TEST(MazeGenerator, BigMaze) {
  MazeGenerator maze_gen;
  Maze maze = maze_gen.GenerateMaze(50, 50);

  EXPECT_EQ(maze.GetRows(), 50);
  EXPECT_EQ(maze.GetCols(), 50);
  EXPECT_EQ(maze.IsIdeal(), true);
}

TEST(MazeGenerator, SmallMaze) {
  MazeGenerator maze_gen;
  Maze maze = maze_gen.GenerateMaze(1, 1);

  EXPECT_EQ(maze.GetRows(), 1);
  EXPECT_EQ(maze.GetCols(), 1);
  EXPECT_EQ(maze.IsIdeal(), true);

  maze = maze_gen.GenerateMaze(2, 2);

  EXPECT_EQ(maze.GetRows(), 2);
  EXPECT_EQ(maze.GetCols(), 2);
  EXPECT_EQ(maze.IsIdeal(), true);
}

TEST(MazeGenerator, StressTest) {
  MazeGenerator maze_gen;
  for (int i = 0; i < 100; i++) {
    Maze maze = maze_gen.GenerateMaze(15, 15);

    EXPECT_EQ(maze.GetRows(), 15);
    EXPECT_EQ(maze.GetCols(), 15);
    EXPECT_EQ(maze.IsIdeal(), true);
  }
}

TEST(MazeGenerator, Chances) {
  MazeGenerator maze_gen;
  Maze maze = maze_gen.GenerateMaze(20, 20, 1.0f, 0.0f);

  EXPECT_EQ(maze.GetRows(), 20);
  EXPECT_EQ(maze.GetCols(), 20);
  EXPECT_EQ(maze.IsIdeal(), true);

  maze = maze_gen.GenerateMaze(20, 20, 0.0f, 1.0f);

  EXPECT_EQ(maze.GetRows(), 20);
  EXPECT_EQ(maze.GetCols(), 20);
  EXPECT_EQ(maze.IsIdeal(), true);

  maze = maze_gen.GenerateMaze(20, 20, 0.0f, 0.0f);

  EXPECT_EQ(maze.GetRows(), 20);
  EXPECT_EQ(maze.GetCols(), 20);
  EXPECT_EQ(maze.IsIdeal(), true);

  maze = maze_gen.GenerateMaze(20, 20, 1.0f, 1.0f);

  EXPECT_EQ(maze.GetRows(), 20);
  EXPECT_EQ(maze.GetCols(), 20);
  EXPECT_EQ(maze.IsIdeal(), true);
}

TEST(MazeGenerator, BrokenSize) {
  MazeGenerator maze_gen;
  EXPECT_THROW(maze_gen.GenerateMaze(0, 0), std::invalid_argument);
  EXPECT_THROW(maze_gen.GenerateMaze(-1, 5), std::invalid_argument);
}
