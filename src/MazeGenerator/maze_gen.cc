#include "maze_gen.h"

s21::MazeGenerator::MazeGenerator() {
    next_set = 0;
}

s21::Maze s21::MazeGenerator::generateMaze(int rows, int cols) {
    Maze maze(rows, cols);
    maze.GetMatrix() = std::vector<s21::Border>(rows * cols, NO_BORDER);
    cells = std::vector<int>(cols, -1);

    for (size_t row = 0; row < rows - 1; row++) {
        FillEmptyCells(cols);
        AddRightWalls(maze, row);
        AddBottomWalls(maze, row);
    }
    AddEndLine(maze);

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

void s21::MazeGenerator::AddRightWalls(Maze& maze, int row) {
    for (size_t cell = 0; cell < maze.GetCols() - 1; cell++) {
        if (randomChoice() || cells[cell] == cells[cell + 1]) {
            maze.GetMatrix()[row * maze.GetCols() + cell] = RIGHT_BORDER;
        } else {
            mergeSets(cells[cell], cells[cell + 1]);
        }
        maze.GetMatrix()[(row + 1) * maze.GetCols() - 1] = RIGHT_BORDER;
    }
}

void s21::MazeGenerator::AddBottomWalls(Maze &maze, int row) {
    for (size_t cell = 0; cell < maze.GetCols(); cell++) {
        auto bottom_borders = 
            std::count_if(sets[cell].begin(), sets[cell].end(), 
                    [&maze, row](int c) { return maze.GetMatrix()[row * maze.GetCols() + c] == BOTTOM_BORDER ||
                                                 maze.GetMatrix()[row * maze.GetCols() + c] == BOTH_BORDER; });

        if (randomChoice() && sets[cell].size() != 1 && bottom_borders != sets[cell].size() - 1) {
            maze.GetMatrix()[row * maze.GetCols() + cell] = 
                (maze.GetMatrix()[row * maze.GetCols() + cell] == RIGHT_BORDER ? BOTH_BORDER : BOTTOM_BORDER);


            sets[cells[cell]].erase(std::find(sets[cells[cell]].begin(), sets[cells[cell]].end(), cell));
            cells[cell] = kEmptyCell;
        }
    }
}

void s21::MazeGenerator::AddEndLine(Maze &maze) {
    FillEmptyCells(maze.GetCols());
    AddRightWalls(maze, maze.GetRows() - 1);

    for (size_t cell = 0; cell < maze.GetCols() - 1; cell++) {
        if (cells[cell] != cells[cell + 1]) {
            maze.GetMatrix()[(maze.GetRows() - 1) * maze.GetCols() + cell] = BOTTOM_BORDER;
            mergeSets(cells[cell], cells[cell + 1]);
        }
        maze.GetMatrix()[(maze.GetRows() - 1) * maze.GetCols() + cell] = 
            maze.GetMatrix()[(maze.GetRows() - 1) * maze.GetCols() + cell] == RIGHT_BORDER ? BOTH_BORDER : BOTTOM_BORDER;
    }
    maze.GetMatrix()[maze.GetRows() * maze.GetCols() - 1] = BOTH_BORDER;
}

bool s21::MazeGenerator::randomChoice() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution bd;

    return bd(gen);
}

void s21::MazeGenerator::mergeSets(size_t current_set_id, size_t target_set_id) {
    for (auto target_cell : sets[target_set_id]) {
        cells[target_cell] = current_set_id;

        auto& vec = sets[current_set_id];
        vec.insert(std::upper_bound(vec.begin(), vec.end(), target_cell), target_cell);
    }
    sets.erase(target_set_id);
}

int main() {
    std::atexit([]() { std::cout << "\n\nsuccess exit\n"; });
    std::signal(SIGSEGV, [](int sig) { std::cout << "\n\nSegmentation fault\n"; });
    s21::MazeGenerator mg;

    s21::Maze maze = mg.generateMaze(4, 4);
    
    // std::cout << maze.GetCols() << " * " << maze.GetRows() << std::endl;
    // std::cout << "Maze: " << maze.GetMatrix().size() << std::endl;
    for (int i = 0; i < maze.GetMatrix().size(); i++) {
        if (i % maze.GetCols() == 0) std::cout << "\n|";
        // std::cout << maze.GetMatrix()[i] << " ";
        switch (maze.GetMatrix()[i])
        {
        case s21::Border::NO_BORDER:
            std::cout << "    ";
            break;
        case s21::Border::RIGHT_BORDER:
            std::cout << "   |";
            break;
        case s21::Border::BOTTOM_BORDER:
            std::cout << "___ ";
            break;
        case s21::Border::BOTH_BORDER:
            std::cout << "___|";
            break;
        }
        // std::cout << " ";
    }
    // std::cout << std::endl;
    // std::cout << mg.randomChoice();
}
