#ifndef MAZE_H
#define MAZE_H

#include <vector>

namespace s21 {
    struct Maze {
        Maze(int width, int height) : width(width), height(height) {}

        int width;
        int height;

        std::vector<std::vector<int>> horizontals;
        std::vector<std::vector<int>> verticals;
    };
}

#endif
