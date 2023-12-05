#include "../models/maze_generator.h"
#include <csignal>

int main() {
    std::atexit([]() { std::cout << "\n\nsuccess exit\n"; });
    std::signal(SIGSEGV, [](int sig) { std::cout << sig << "\n\nSegmentation fault\n"; });
    s21::MazeGenerator mg;

    s21::Maze maze = mg.generateMaze(10, 10);
    
    for (int i = 0; i < maze.GetCols(); i++) std::cout << " ___";

    for (size_t i = 0; i < maze.GetMatrix().size(); i++) {
        if (i % maze.GetCols() == 0) std::cout << "\n|";
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
    }
}