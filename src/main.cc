#include <QApplication>

#include "controllers/controller_singleton.h"
#include "models/model.h"
#include "models/render/render_context.h"
#include "views/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  s21::RenderContext render_context;
  s21::Model model = s21::Model(&render_context);

  s21::ControllerSingleton &controller = s21::ControllerSingleton::GetInstance();
  controller.SetModel(&model);

  MainWindow *window = new MainWindow();

  // window->setWindowTitle(QString("Maze"));
  window->show();

  return a.exec();
}
