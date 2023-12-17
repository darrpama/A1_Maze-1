#include "cave_generator.h"

namespace s21 {

CaveGenerator::CaveGenerator() { Clear(); }

Cave CaveGenerator::Generate(size_t rows, size_t cols, float chance) {
  if (rows < 1 || cols < 1) {
    throw std::invalid_argument("Invalid cave size");
  }
  Cave cave(rows, cols);
  cave.GetMatrix() = std::vector<unsigned>(rows * cols, 0);
  cells_ = std::vector<unsigned>(cols, 0);
  for (size_t row = 0; row < rows; row++) {
    for (size_t cell = 0; cell < cols; cell++) {
      cave.GetMatrix()[row * cols + cell] = (RandomChoice(chance)) ? 1 : 0;
    }
  }
  Clear();

  return cave;
}

bool CaveGenerator::RandomChoice(float chance) {
  std::mt19937 gen(std::random_device{}());
  std::bernoulli_distribution bd(chance);

  return bd(gen);
}

/*

Правила проще, чем в "Жизни" -
есть две специальные переменные,
  правило для "рождения" "мертвых" клеток (предел "рождения")
  правило для уничтожения "живых" клеток (предел "смерти").

DeathRule for Alive Cells
  Если "живая" клетка окружены "живыми" клетками,
  количество которых меньше, чем предел "смерти",
  они "умирают".

LifeRule for Dead Cells
  Если "мертвая" клетка находятся рядом с "живыми",
  количество которых больше, чем предел "рождения",
  они становятся "живыми".

Живая клетка Alive Cell (AC)
Мертвая клетка Dead Cell (DC)

Окружающие живые клетки Alive Neighbors (AN)

*/

void CaveGenerator::Step(Cave *cave, unsigned die_limit, unsigned born_limit) {
  rows_ = cave->GetRows();
  cols_ = cave->GetCols();
  unsigned alive_neighbors_count = 0;

  for (size_t row = 0; row < rows_; row++) {
    for (size_t col = 0; col < cols_; col++) {
      alive_neighbors_count = GetAliveNeigborsCount(cave, row, col);
      if (cave->GetMatrix()[row * cols_ + col] ==
          1) {  // alive cell (death rule)
        if (alive_neighbors_count < die_limit) {
          cave->GetMatrix()[row * cols_ + col] = 0;
        }
      } else {  // death cell (alive rule)
        if (alive_neighbors_count > born_limit) {
          cave->GetMatrix()[row * cols_ + col] = 1;
        }
      }
    }
  }
}

size_t CaveGenerator::GetAliveNeigborsCount(Cave *cave, size_t row,
                                            size_t col) {
  return GetNorthWest(cave, row, col) + GetNorth(cave, row, col) +
         GetNorthEast(cave, row, col) + GetEast(cave, row, col) +
         GetSouthEast(cave, row, col) + GetSouth(cave, row, col) +
         GetSouthWest(cave, row, col) + GetWest(cave, row, col);
}

size_t CaveGenerator::GetNorthWest(Cave *cave, size_t row, size_t col) {
  return (((row - 1) < 0) || ((col - 1) < 0))
             ? 1
             : cave->GetMatrix()[(row - 1) * cols_ + (col - 1)];
}

size_t CaveGenerator::GetNorth(Cave *cave, size_t row, size_t col) {
  return ((row - 1) < 0) ? 1 : cave->GetMatrix()[(row - 1) * cols_ + col];
}

size_t CaveGenerator::GetNorthEast(Cave *cave, size_t row, size_t col) {
  return (((row - 1) < 0) || ((col + 1) >= cols_))
             ? 1
             : cave->GetMatrix()[(row - 1) * cols_ + (col + 1)];
}

size_t CaveGenerator::GetEast(Cave *cave, size_t row, size_t col) {
  return ((col + 1) >= cols_) ? 1 : cave->GetMatrix()[row * cols_ + (col + 1)];
}

size_t CaveGenerator::GetSouthEast(Cave *cave, size_t row, size_t col) {
  return (((row + 1) >= rows_) || ((col + 1) >= cols_))
             ? 1
             : cave->GetMatrix()[(row + 1) * cols_ + (col + 1)];
}

size_t CaveGenerator::GetSouth(Cave *cave, size_t row, size_t col) {
  return ((row + 1) >= rows_) ? 1 : cave->GetMatrix()[(row + 1) * cols_ + col];
}

size_t CaveGenerator::GetSouthWest(Cave *cave, size_t row, size_t col) {
  return (((row + 1) >= rows_) || ((col - 1) < 0))
             ? 1
             : cave->GetMatrix()[(row + 1) * cols_ + (col - 1)];
}

size_t CaveGenerator::GetWest(Cave *cave, size_t row, size_t col) {
  return ((col - 1) < 0) ? 1 : cave->GetMatrix()[row * cols_ + (col - 1)];
}

void CaveGenerator::Clear() { cells_.clear(); }

}  // namespace s21
