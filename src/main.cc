#include <QApplication>

#include "controllers/controller_singleton.h"
#include "models/model.h"
<<<<<<< HEAD
#include "views/canvas.h"
=======
#include "models/maze.h"
#include "models/maze_parser.h"
#include "models/cave.h"
#include "models/cave_parser.h"
>>>>>>> added cave upload, parse and render;
#include "views/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);


  MainWindow *window = new MainWindow();

<<<<<<< HEAD
  s21::Model model = s21::Model();
=======
  s21::Maze maze = s21::Maze(0, 0);
  s21::MazeParser maze_parser = s21::MazeParser(&maze);
  s21::MazeGenerator maze_generator = s21::MazeGenerator();

  s21::Cave cave = s21::Cave(0, 0);
  s21::CaveParser cave_parser = s21::CaveParser(&cave);

  s21::Model model = s21::Model(&maze, &maze_parser, &maze_generator, &cave, &cave_parser);
>>>>>>> added cave upload, parse and render;
  s21::ControllerSingleton &controller = s21::ControllerSingleton::GetInstance();
  controller.SetModel(&model);

  // window->setWindowTitle(QString("Maze"));
  window->show();

  return a.exec();
}
