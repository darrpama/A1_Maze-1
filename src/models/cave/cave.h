#ifndef A1_MAZE_1_0_SRC_MODEL_CAVE_H
#define A1_MAZE_1_0_SRC_MODEL_CAVE_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <random>
#include <sstream>
#include <vector>

#include "../type.h"
#include "../utils.h"

namespace s21 {

class Cave {
 public:
  Cave();
  Cave(int rows, int cols);

  int GetRows();
  int GetCols();
  void SetRows(int rows);
  void SetCols(int cols);
  std::vector<unsigned> &GetMatrix();

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
