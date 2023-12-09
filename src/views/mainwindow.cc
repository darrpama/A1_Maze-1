#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui_(new Ui::MainWindow)
{
  ui_->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui_;
}

void MainWindow::on_upload_btn_clicked() {
  QString file_path = QFileDialog::getOpenFileName(
    this, tr("Select File"), "", tr("All Files (*.*)")
  );
  if (!file_path.isEmpty()) {
    std::string filepath = file_path.toStdString();
    s21::ControllerSingleton::GetInstance().UploadMaze(filepath);
  }
}

void MainWindow::on_generate_btn_clicked() {
  s21::ControllerSingleton::GetInstance().GenerateMaze(ui_->rows_input->value(), ui_->cols_input->value());
  ui_->maze_canvas->update();
}

void MainWindow::on_cave_upload_btn_clicked() {
  QString file_path = QFileDialog::getOpenFileName(
    this, tr("Select File"), "", tr("All Files (*.*)")
  );
  if (!file_path.isEmpty()) {
    std::string filepath = file_path.toStdString();
    s21::ControllerSingleton::GetInstance().UploadCave(filepath);
  }
}

