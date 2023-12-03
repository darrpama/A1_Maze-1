#include "views/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  
  MainWindow *window = new MainWindow();

  window->setWindowTitle(QString("Maze"));
  window->show();


  return a.exec();
}
