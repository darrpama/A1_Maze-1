#include "models/model.h"
#include "Controllers/controller.h"
#include "views/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  s21::Model model = s21::Model();

  s21::Controller controller = s21::Controller(&model);
  
  MainWindow *window = new MainWindow();

  window->setWindowTitle(QString("Maze"));
  window->show();

  return a.exec();
}
