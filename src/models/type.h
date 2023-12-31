#ifndef A1_MAZE_1_SRC_TYPE_H
#define A1_MAZE_1_SRC_TYPE_H

#include <stddef.h>

namespace s21 {

enum Border {
  NO_BORDER = 0,
  RIGHT_BORDER,
  BOTTOM_BORDER,
  BOTH_BORDER,
};

struct Vector2D {
  size_t x_;
  size_t y_;

  Vector2D(size_t x, size_t y) : x_(x), y_(y) {}
};

}  // namespace s21

#endif  // A1_MAZE_1_SRC_TYPE_H
