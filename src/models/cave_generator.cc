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
    for (size_t col = 0; col < cols; col++) {
      cave.GetMatrix()[row * cols + col] = (RandomChoice(chance)) ? 1 : 0;
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
Правила:
    правило для "рождения" "мертвых" клеток (предел "рождения")
        Если "живая" клетка окружены "живыми" клетками, 
        количество которых меньше, чем предел "смерти", 
        они "умирают".
    правило для уничтожения "живых" клеток (предел "смерти").
        Если "мертвая" клетка находятся рядом с "живыми", 
        количество которых больше, чем предел "рождения", 
        они становятся "живыми".
*/

bool CaveGenerator::Step(Cave *cave, unsigned die_limit, unsigned born_limit) {
  Cave old_cave = *cave;
  Cave new_cave = *cave;

  rows_ = cave->GetRows();
  cols_ = cave->GetCols();
  current_col_ = 0;
  current_row_ = 0;
  unsigned alive_neighbors_count = 0;

  for (size_t row = 0; row < rows_; row++) {
    current_row_ = row;
    for (size_t col = 0; col < cols_; col++) {
      current_col_ = col;
      alive_neighbors_count = GetAliveNeigborsCount(&new_cave);
      if (new_cave.GetMatrix()[row * cols_ + col] == 1) {  
        // alive cell (death rule)
        if (alive_neighbors_count < die_limit) {
          new_cave.GetMatrix()[row * cols_ + col] = 0;
        }
      } else {  
        // death cell (alive rule)
        if (alive_neighbors_count > born_limit) {
          new_cave.GetMatrix()[row * cols_ + col] = 1;
        }
      }
    }
  }

  cave->SetCols(new_cave.GetCols());
  cave->SetRows(new_cave.GetRows());
  cave->SetMatrix(new_cave.GetMatrix());

  return CompareCaves(&old_cave, cave);
}

bool CaveGenerator::CompareCaves(Cave *old_cave, Cave *new_cave) {
  if (old_cave->GetRows() != new_cave->GetRows()) {
    return false;
  }
  if (old_cave->GetCols() != new_cave->GetCols()) {
    return false;
  }
  for (size_t i = 0; i < old_cave->GetRows(); i++) {
    for (size_t j = 0; j < old_cave->GetCols(); j++) {
      bool old_cave_value = old_cave->GetMatrix()[i * old_cave->GetCols() + j];
      bool new_cave_value = new_cave->GetMatrix()[i * new_cave->GetCols() + j];
      if (old_cave_value != new_cave_value) {
        return false;
      }
    }
  }
  return true;
}

size_t CaveGenerator::GetAliveNeigborsCount(Cave *cave) {
  return GetNorthWest(cave) + GetNorth(cave)
       + GetNorthEast(cave) + GetEast(cave)
       + GetSouthEast(cave) + GetSouth(cave)
       + GetSouthWest(cave) + GetWest(cave);
}

size_t CaveGenerator::GetNorthWest(Cave *cave) {
  return (((current_row_ - 1) < 0) || ((current_col_ - 1) < 0)) ? 1 
    : cave->GetMatrix()[(current_row_ - 1) * cols_ + (current_col_ - 1)];
}

size_t CaveGenerator::GetNorth(Cave *cave) {
  return ((current_row_ - 1) < 0) ? 1 
    : cave->GetMatrix()[(current_row_ - 1) * cols_ + current_col_];
}

size_t CaveGenerator::GetNorthEast(Cave *cave) {
  return (((current_row_ - 1) < 0) || ((current_col_ + 1) >= cols_)) ? 1 
    : cave->GetMatrix()[(current_row_ - 1) * cols_ + (current_col_ + 1)];
}

size_t CaveGenerator::GetEast(Cave *cave) {
  return ((current_col_ + 1) >= cols_) ? 1 
    : cave->GetMatrix()[current_row_ * cols_ + (current_col_ + 1)];
}

size_t CaveGenerator::GetSouthEast(Cave *cave) {
  return (((current_row_ + 1) >= rows_) || ((current_col_ + 1) >= cols_)) ? 1 
    : cave->GetMatrix()[(current_row_ + 1) * cols_ + (current_col_ + 1)];
}

size_t CaveGenerator::GetSouth(Cave *cave) {
  return ((current_row_ + 1) >= rows_) ? 1 
    : cave->GetMatrix()[(current_row_ + 1) * cols_ + current_col_];
}

size_t CaveGenerator::GetSouthWest(Cave *cave) {
  return (((current_row_ + 1) >= rows_) || ((current_col_ - 1) < 0)) ? 1 
    : cave->GetMatrix()[(current_row_ + 1) * cols_ + (current_col_ - 1)];
}

size_t CaveGenerator::GetWest(Cave *cave) {
  return ((current_col_ - 1) < 0) ? 1 
    : cave->GetMatrix()[current_row_ * cols_ + (current_col_ - 1)];
}

void CaveGenerator::Clear() {
  cells_.clear();
}

}  // namespace s21
