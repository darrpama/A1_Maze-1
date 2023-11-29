#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui_(new Ui::MainWindow)
{
  ui_->setupUi(this);
//   canvas_ = findChild<Canvas*>("canvas");
}

MainWindow::~MainWindow() {
  delete ui_;
}
