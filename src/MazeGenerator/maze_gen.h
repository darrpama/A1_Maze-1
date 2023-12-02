#ifndef MAZE_GEN_H
#define MAZE_GEN_H

#include <vector>
#include "maze.h"

namespace s21 {
    class MazeGenerator {
       public:
        MazeGenerator();
        Maze generateMaze(int width, int height);
       
       private:
        int next_set;
    };
}

#endif
