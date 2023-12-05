#include "maze_generator.h"

namespace s21 {
    MazeGenerator::MazeGenerator() { Clear(); }

    Maze MazeGenerator::generateMaze(int rows, int cols, float right_wall_chance, float bottom_wall_chance) {
        if (rows < 1 || cols < 1)
            throw std::invalid_argument("Invalid maze size");

        this->next_set_ = 0;
        Maze maze(rows, cols);
        maze.GetMatrix() = std::vector<Border>(rows * cols, NO_BORDER);
        cells_ = std::vector<int>(cols, kEmptyCell);

        for (size_t row = 0; row < static_cast<size_t>(rows - 1); row++) {
            FillEmptyCells(cols);
            AddRightWalls(maze, row, right_wall_chance);
            AddBottomWalls(maze, row, bottom_wall_chance);
        }
        AddEndLine(maze, right_wall_chance);
        Clear();

        return maze;
    }

    void MazeGenerator::FillEmptyCells(int cols) {
        for (size_t cell = 0; cell < static_cast<size_t>(cols); cell++) {
            if (cells_[cell] == kEmptyCell) {
                size_t set = next_set_++;
                sets_[set].push_back(cell);
                cells_[cell] = set;
            }
        }
    }

    void MazeGenerator::AddRightWalls(Maze& maze, int row, float right_wall_chance) {
        for (size_t cell = 0; cell < static_cast<size_t>(maze.GetCols() - 1); cell++) {
            if (RandomChoice(right_wall_chance) || cells_[cell] == cells_[cell + 1]) {
                maze.GetMatrix()[row * maze.GetCols() + cell] = RIGHT_BORDER;
            } else {
                MergeSets(cells_[cell], cells_[cell + 1]);
            }
            maze.GetMatrix()[(row + 1) * maze.GetCols() - 1] = RIGHT_BORDER;
        }
    }

    void MazeGenerator::AddBottomWalls(Maze &maze, int row, float bottom_wall_chance) {
        for (size_t cell = 0; cell < static_cast<size_t>(maze.GetCols()); cell++) {
            int cur_cell = cells_[cell];
            size_t bottom_borders = 
                std::count_if(sets_[cells_[cell]].begin(), sets_[cur_cell].end(), 
                        [&maze, row](int c) { return maze.GetMatrix()[row * maze.GetCols() + c] == BOTTOM_BORDER ||
                                                    maze.GetMatrix()[row * maze.GetCols() + c] == BOTH_BORDER; });

            if (RandomChoice(bottom_wall_chance) && sets_[cur_cell].size() != 1 && bottom_borders != sets_[cur_cell].size() - 1) {
                maze.GetMatrix()[row * maze.GetCols() + cell] = 
                    (maze.GetMatrix()[row * maze.GetCols() + cell] == RIGHT_BORDER ? BOTH_BORDER : BOTTOM_BORDER);
        
                sets_[cells_[cell]].erase(std::find(sets_[cells_[cell]].begin(), sets_[cells_[cell]].end(), cell));
                cells_[cell] = kEmptyCell;
            }
            
        }
    }

    void MazeGenerator::AddEndLine(Maze &maze, float right_wall_chance) {
        FillEmptyCells(maze.GetCols());
        AddRightWalls(maze, maze.GetRows() - 1, right_wall_chance);

        for (size_t cell = 0; cell < static_cast<size_t>(maze.GetCols() - 1); cell++) {
            if (cells_[cell] != cells_[cell + 1]) {
                maze.GetMatrix()[(maze.GetRows() - 1) * maze.GetCols() + cell] = BOTTOM_BORDER;
                MergeSets(cells_[cell], cells_[cell + 1]);
            }
            maze.GetMatrix()[(maze.GetRows() - 1) * maze.GetCols() + cell] = 
                maze.GetMatrix()[(maze.GetRows() - 1) * maze.GetCols() + cell] == RIGHT_BORDER ? BOTH_BORDER : BOTTOM_BORDER;
        }
        maze.GetMatrix()[maze.GetRows() * maze.GetCols() - 1] = BOTH_BORDER;
    }

    bool MazeGenerator::RandomChoice(float chance) {
        std::mt19937 gen(std::random_device{}());
        std::bernoulli_distribution bd(chance);

        return bd(gen);
    }

    void MazeGenerator::MergeSets(size_t current_set_id, size_t target_set_id) {
        for (auto target_cell : sets_[target_set_id]) {
            cells_[target_cell] = current_set_id;

            auto& vec = sets_[current_set_id];
            vec.insert(std::upper_bound(vec.begin(), vec.end(), target_cell), target_cell);
        }
        sets_.erase(target_set_id);
    }

    void MazeGenerator::Clear() {
        this->next_set_ = 0;
        sets_.clear();
        cells_.clear();
    }
}  // namespace s21
