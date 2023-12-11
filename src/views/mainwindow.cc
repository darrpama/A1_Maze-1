#include <iostream>

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

void MainWindow::on_cave_init_random_btn_clicked() {
  s21::ControllerSingleton::GetInstance().GenerateCave(
    static_cast<unsigned>(ui_->cave_rows->value()),
    static_cast<unsigned>(ui_->cave_cols->value()),
    static_cast<float>(ui_->cave_cell_chance->value())
  );
  ui_->cave_canvas->update();
}

void MainWindow::on_step_render_btn_clicked() {
  s21::ControllerSingleton::GetInstance().StepRender(
    static_cast<unsigned>(ui_->die_limit_input->value()),
    static_cast<unsigned>(ui_->born_limit_input->value())
  );
  ui_->cave_canvas->update();
}

