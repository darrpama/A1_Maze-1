#ifndef A1_MAZE_1_0_SRC_MODEL_CAVE_H
#define A1_MAZE_1_0_SRC_MODEL_CAVE_H

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>

#include "../type.h"

namespace s21 {

class Cave {
 public:
  Cave() : rows_{}, cols_{}, matrix_{} {}
  Cave(int rows, int cols) : rows_(rows), cols_(cols), matrix_{} {}
  ~Cave() = default;

  std::vector<unsigned>& GetMatrix();
  int GetRows();
  int GetCols();
  void SetRows(int);
  void SetCols(int);

  void Clear();

  // generator
  void Generate(int, int, float);
  bool StepRender(unsigned, unsigned);

  // parser
  void ParseFromFile(std::string);

 private:
  int rows_;
  int cols_;
  std::vector<unsigned> matrix_;

  bool RandomChoice(float);
  bool CompareCaves(Cave *, Cave *);
  int GetAliveNeigborsCount(Cave *, int, int);

  void CheckAndFixEndLine(std::string);
  void ParseSize(const std::string &);
  void ParseMatrix(const std::string &);
};

}  // namespace s21

#endif  // A1_MAZE_1_0_SRC_MODEL_CAVE_H
