#include "cave_generator.h"

namespace s21 {
CaveGenerator::CaveGenerator() { Clear(); }

Cave CaveGenerator::Generate(size_t rows, size_t cols, float chance) {
  if (rows < 1 || cols < 1)
      throw std::invalid_argument("Invalid maze size");

  Cave cave(rows, cols);
  cave.GetMatrix() = std::vector<unsigned>(rows * cols, 0);
  cells_ = std::vector<unsigned>(cols, 0);

  for (size_t row = 0; row < static_cast<size_t>(rows - 1); row++) {
    AddCell(cave, row, chance);
  }
  Clear();

  return cave;
}

bool CaveGenerator::RandomChoice(float chance) {
  std::mt19937 gen(std::random_device{}());
  std::bernoulli_distribution bd(chance);

  return bd(gen);
}

void CaveGenerator::AddCell(Cave& cave, size_t row, float chance) {
  unsigned value = 0;
  for (size_t cell = 0; cell < cave.GetCols() - 1; cell++) {
    value = (RandomChoice(chance)) ? 1 : 0;
    cave.GetMatrix()[row * cave.GetCols() + cell] = value;
  }
}

void CaveGenerator::Clear() {
    cells_.clear();
}

}  // namespace s21
