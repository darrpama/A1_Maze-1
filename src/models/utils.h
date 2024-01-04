#ifndef A1_MAZE_1_0_SRC_MODEL_UTILS_H
#define A1_MAZE_1_0_SRC_MODEL_UTILS_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <random>
#include <sstream>
#include <vector>

#include "type.h"

namespace s21 {

class Utils {
 public:
  static bool RandomChoice(float chance) {
    std::mt19937 gen(std::random_device{}());
    std::bernoulli_distribution bd(chance);

    return bd(gen);
  }

  static void CheckAndFixEndLine(const std::string &filepath) {
    FILE *fp = fopen(filepath.c_str(), "r+");
    if (fp == NULL) {
      throw std::invalid_argument("Failed to open file: " +
                                  filepath);  // LCOV_EXCL_LINE
    }
    fseek(fp, -1, SEEK_END);
    char c = fgetc(fp);
    if (c != '\n') {
      fseek(fp, -1, SEEK_END);  // LCOV_EXCL_LINE
      fputc('\n', fp);          // LCOV_EXCL_LINE
    }
    fclose(fp);
  }
};

}  // namespace s21

#endif  // A1_MAZE_1_0_SRC_MODEL_UTILS_H
