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
#include "../utils.h"

namespace s21 {

class Cave {
 public:
  Cave() : matrix_{}, rows_{}, cols_{} {}
  Cave(int rows, int cols) : matrix_{}, rows_(rows), cols_(cols) {}

  int GetRows() { return rows_; }
  int GetCols() { return cols_; }
  void SetRows(int rows) { rows_ = rows; }
  void SetCols(int cols) { cols_ = cols; }
  std::vector<unsigned>& GetMatrix() { return matrix_; }
  
  void Generate(int, int, float);
  bool StepRender(unsigned, unsigned);
  void ParseFromFile(std::string);

 private:
  std::vector<unsigned> matrix_;
  int rows_;
  int cols_;
  unsigned die_limit_;
  unsigned born_limit_;

  void Clear();
  bool CompareCaves(Cave *, Cave *);
  int GetAliveNeigborsCount(Cave *, int, int);
  void ParseSize(const std::string &);
  void ParseMatrix(const std::string &);
  void ApplyRules(unsigned index, unsigned alive_neighbors_count);
};

}  // namespace s21

#endif  // A1_MAZE_1_0_SRC_MODEL_CAVE_H
