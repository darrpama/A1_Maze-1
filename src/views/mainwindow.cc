#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui_(new Ui::MainWindow)
{
  s21::ControllerSingleton::GetInstance().InitRender(s21::RenderType::MAZE);
  ui_->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui_;
}
