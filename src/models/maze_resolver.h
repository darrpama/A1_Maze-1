#ifndef A1_MAZE_1_0_SRC_MAZE_RESOLVER_H
#define A1_MAZE_1_0_SRC_MAZE_RESOLVER_H

#include <algorithm>
#include <vector>
#include <random>
#include <unordered_map>
#include "maze.h"

namespace s21 {
    class MazeResolver {
       public:
        MazeResolver();
        void ResolveMaze();
       
       private:
        void Clear();
    };
}

#endif  // A1_MAZE_1_0_SRC_MAZE_RESOLVER_H
