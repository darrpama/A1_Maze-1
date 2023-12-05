#include "maze_generator.h"

s21::MazeGenerator::MazeGenerator() { Clear(); }

s21::Maze s21::MazeGenerator::generateMaze(int rows, int cols, float right_wall_chance, float bottom_wall_chance) {
    if (rows < 1 || cols < 1)
        throw std::invalid_argument("Invalid maze size");

    this->next_set = 0;
    Maze maze(rows, cols);
    maze.GetMatrix() = std::vector<s21::Border>(rows * cols, NO_BORDER);
    cells = std::vector<int>(cols, kEmptyCell);

    for (size_t row = 0; row < rows - 1; row++) {
        FillEmptyCells(cols);
        AddRightWalls(maze, row, right_wall_chance);
        AddBottomWalls(maze, row, bottom_wall_chance);
    }
    AddEndLine(maze, right_wall_chance);
    Clear();

    return maze;
}

void s21::MazeGenerator::FillEmptyCells(int cols) {
    for (size_t cell = 0; cell < cols; cell++) {
        if (cells[cell] == kEmptyCell) {
            size_t set = next_set++;
            sets[set].push_back(cell);
            cells[cell] = set;
        }
    }
}

void s21::MazeGenerator::AddRightWalls(Maze& maze, int row, float right_wall_chance) {
    for (size_t cell = 0; cell < maze.GetCols() - 1; cell++) {
        if (RandomChoice(right_wall_chance) || cells[cell] == cells[cell + 1]) {
            maze.GetMatrix()[row * maze.GetCols() + cell] = RIGHT_BORDER;
        } else {
            MergeSets(cells[cell], cells[cell + 1]);
        }
        maze.GetMatrix()[(row + 1) * maze.GetCols() - 1] = RIGHT_BORDER;
    }
}

void s21::MazeGenerator::AddBottomWalls(Maze &maze, int row, float bottom_wall_chance) {
    for (size_t cell = 0; cell < maze.GetCols(); cell++) {
        int cur_cell = cells[cell];
        auto bottom_borders = 
            std::count_if(sets[cells[cell]].begin(), sets[cur_cell].end(), 
                    [&maze, row](int c) { return maze.GetMatrix()[row * maze.GetCols() + c] == BOTTOM_BORDER ||
                                                 maze.GetMatrix()[row * maze.GetCols() + c] == BOTH_BORDER; });

        if (RandomChoice(bottom_wall_chance) && sets[cur_cell].size() != 1 && bottom_borders != sets[cur_cell].size() - 1) {
            maze.GetMatrix()[row * maze.GetCols() + cell] = 
                (maze.GetMatrix()[row * maze.GetCols() + cell] == RIGHT_BORDER ? BOTH_BORDER : BOTTOM_BORDER);
     
            sets[cells[cell]].erase(std::find(sets[cells[cell]].begin(), sets[cells[cell]].end(), cell));
            cells[cell] = kEmptyCell;
        }
        
    }
}

void s21::MazeGenerator::AddEndLine(Maze &maze, float right_wall_chance) {
    FillEmptyCells(maze.GetCols());
    AddRightWalls(maze, maze.GetRows() - 1, right_wall_chance);

    for (size_t cell = 0; cell < maze.GetCols() - 1; cell++) {
        if (cells[cell] != cells[cell + 1]) {
            maze.GetMatrix()[(maze.GetRows() - 1) * maze.GetCols() + cell] = BOTTOM_BORDER;
            MergeSets(cells[cell], cells[cell + 1]);
        }
        maze.GetMatrix()[(maze.GetRows() - 1) * maze.GetCols() + cell] = 
            maze.GetMatrix()[(maze.GetRows() - 1) * maze.GetCols() + cell] == RIGHT_BORDER ? BOTH_BORDER : BOTTOM_BORDER;
    }
    maze.GetMatrix()[maze.GetRows() * maze.GetCols() - 1] = BOTH_BORDER;
}

bool s21::MazeGenerator::RandomChoice(float chance) {
    std::mt19937 gen(std::random_device{}());
    std::bernoulli_distribution bd(chance);

    return bd(gen);
}

void s21::MazeGenerator::MergeSets(size_t current_set_id, size_t target_set_id) {
    for (auto target_cell : sets[target_set_id]) {
        cells[target_cell] = current_set_id;

        auto& vec = sets[current_set_id];
        vec.insert(std::upper_bound(vec.begin(), vec.end(), target_cell), target_cell);
    }
    sets.erase(target_set_id);
}

void s21::MazeGenerator::Clear() {
    this->next_set = 0;
    sets.clear();
    cells.clear();
}
