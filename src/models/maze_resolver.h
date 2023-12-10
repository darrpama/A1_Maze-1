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
        explicit MazeResolver(Maze &maze) : maze_(&maze){};
        std::vector<std::pair<size_t, size_t>> Resolve(std::pair<size_t, size_t>, std::pair<size_t, size_t>);
       
       private:
        Maze *maze_;
    };

}  // namespace s21

#endif  // A1_MAZE_1_0_SRC_MAZE_RESOLVER_H
