#include <QApplication>

#include "controllers/controller_singleton.h"
#include "models/cave/cave.h"
#include "models/maze/maze.h"
#include "models/maze/maze_parser.h"
#include "views/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  MainWindow *window = new MainWindow();

  s21::Maze maze = s21::Maze(0, 0);
  s21::MazeParser maze_parser = s21::MazeParser(&maze);
  s21::MazeGenerator maze_generator = s21::MazeGenerator();

  s21::Cave cave = s21::Cave(0, 0);

  s21::ControllerSingleton &controller =
      s21::ControllerSingleton::GetInstance();
  controller.SetMaze(&maze);
  controller.SetMazeParser(&maze_parser);
  controller.SetMazeGenerator(&maze_generator);
  controller.SetCave(&cave);

  window->setWindowTitle(QString("Maze"));
  window->show();

  return a.exec();
}
