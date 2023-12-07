#include <QApplication>

#include "controllers/controller_singleton.h"
#include "models/model.h"
#include "views/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);


  MainWindow *window = new MainWindow();

  s21::Model model = s21::Model();
  s21::ControllerSingleton &controller = s21::ControllerSingleton::GetInstance();
  controller.SetModel(&model);

  // window->setWindowTitle(QString("Maze"));
  window->show();

  return a.exec();
}
