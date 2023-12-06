#include "../models/maze_generator.h"
#include <gtest/gtest.h>

s21::MazeGenerator maze_gen;

TEST(MazeGenerator, BigMaze) {
    s21::Maze maze = maze_gen.generateMaze(50, 50);

    EXPECT_EQ(maze.GetRows(), 50);
    EXPECT_EQ(maze.GetCols(), 50);
    EXPECT_EQ(maze.IsIdeal(), true);
}

TEST(MazeGenerator, SmallMaze) {
    s21::Maze maze = maze_gen.generateMaze(1, 1);

    EXPECT_EQ(maze.GetRows(), 1);
    EXPECT_EQ(maze.GetCols(), 1);
    EXPECT_EQ(maze.IsIdeal(), true);

    maze = maze_gen.generateMaze(2, 2);

    EXPECT_EQ(maze.GetRows(), 2);
    EXPECT_EQ(maze.GetCols(), 2);
    EXPECT_EQ(maze.IsIdeal(), true);
}

TEST(MazeGenerator, StressTest) {
    for (int i = 0; i < 100; i++) {
        s21::Maze maze = maze_gen.generateMaze(15, 15);
        
        EXPECT_EQ(maze.GetRows(), 15);
        EXPECT_EQ(maze.GetCols(), 15);
        EXPECT_EQ(maze.IsIdeal(), true);
    }
}

TEST(MazeGenerator, Chances) {
    s21::Maze maze = maze_gen.generateMaze(20, 20, 1.0f, 0.0f);
 
    EXPECT_EQ(maze.GetRows(), 20);
    EXPECT_EQ(maze.GetCols(), 20);
    EXPECT_EQ(maze.IsIdeal(), true);
    
    maze = maze_gen.generateMaze(20, 20, 0.0f, 1.0f);
 
    EXPECT_EQ(maze.GetRows(), 20);
    EXPECT_EQ(maze.GetCols(), 20);
    EXPECT_EQ(maze.IsIdeal(), true);

    maze = maze_gen.generateMaze(20, 20, 0.0f, 0.0f);
 
    EXPECT_EQ(maze.GetRows(), 20);
    EXPECT_EQ(maze.GetCols(), 20);
    EXPECT_EQ(maze.IsIdeal(), true);

    maze = maze_gen.generateMaze(20, 20, 1.0f, 1.0f);
 
    EXPECT_EQ(maze.GetRows(), 20);
    EXPECT_EQ(maze.GetCols(), 20);
    EXPECT_EQ(maze.IsIdeal(), true);
}

TEST(MazeGenerator, BrokenSize) {
    EXPECT_THROW(maze_gen.generateMaze(0, 0), std::invalid_argument);
    EXPECT_THROW(maze_gen.generateMaze(-1, 5), std::invalid_argument);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
