#include "models/model.h"
#include "models/renderer.h"
#include "views/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  
  s21::Renderer renderer = s21::Renderer();
  s21::Model model = s21::Model(&renderer);

  MainWindow *window = new MainWindow();

  window->setWindowTitle(QString("Maze"));
  window->show();

  return a.exec();
}
