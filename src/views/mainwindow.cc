#include "mainwindow.h"

#include <iostream>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);

  emergency_stop_ = false;
  timer_ = new QTimer(this);

  connect(timer_, &QTimer::timeout, this, &MainWindow::TimerCallback);

  connect(ui_->maze_upload_btn, &QAbstractButton::clicked, this,
          &MainWindow::MazeUploadButtonClicked);
  connect(ui_->maze_download_btn, &QAbstractButton::clicked, this,
          &MainWindow::MazeDownloadButtonClicked);
  connect(ui_->maze_init_random_btn, &QAbstractButton::clicked, this,
          &MainWindow::MazeInitRandomButtonClicked);

  connect(ui_->cave_upload_btn, &QAbstractButton::clicked, this,
          &MainWindow::CaveUploadButtonClicked);
  connect(ui_->cave_init_random_btn, &QAbstractButton::clicked, this,
          &MainWindow::CaveInitRandomButtonClicked);

  connect(ui_->cave_step_render_btn, &QAbstractButton::clicked, this,
          &MainWindow::CaveStepRenderButtonClicked);
  connect(ui_->cave_auto_render_btn, &QAbstractButton::clicked, this,
          &MainWindow::CaveAutoRenderButtonClicked);
  connect(ui_->cave_stop_render_btn, &QAbstractButton::clicked, this,
          &MainWindow::CaveStopRenderButtonClicked);
}

MainWindow::~MainWindow() {
  delete timer_;
  delete ui_;
}

void MainWindow::MazeInitRandomButtonClicked() {
  try {
    ui_->maze_canvas->ClearPath();
    s21::ControllerSingleton::GetInstance().GenerateMaze(
        ui_->maze_rows_input->value(), ui_->maze_cols_input->value());

  } catch (const std::exception& e) {
    ShowErrorMessage(e);
  }

  ui_->maze_canvas->update();
}

void MainWindow::MazeUploadButtonClicked() {
  QString file_path = QFileDialog::getOpenFileName(this, tr("Select File"), "",
                                                   tr("All Files (*.*)"));

  if (!file_path.isEmpty()) {
    try {
      std::string filepath = file_path.toStdString();
      s21::ControllerSingleton::GetInstance().UploadMaze(filepath);

      ui_->maze_rows_input->setValue(
          s21::ControllerSingleton::GetInstance().GetMazeRows());
      ui_->maze_cols_input->setValue(
          s21::ControllerSingleton::GetInstance().GetMazeCols());
    } catch (const std::exception& e) {
      ShowErrorMessage(e);
    }
  }

  ui_->maze_canvas->update();
}

void MainWindow::MazeDownloadButtonClicked() {
  QString file_path = QFileDialog::getSaveFileName(this, tr("Select File"), "",
                                                   tr("TXT (*.txt)"));

  try {
    s21::ControllerSingleton::GetInstance().DownloadMaze(
        file_path.toStdString());

  } catch (const std::exception& e) {
    ShowErrorMessage(e);
  }
}

void MainWindow::CaveUploadButtonClicked() {
  QString file_path = QFileDialog::getOpenFileName(this, tr("Select File"), "",
                                                   tr("All Files (*.*)"));

  if (!file_path.isEmpty()) {
    try {
      std::string filepath = file_path.toStdString();
      s21::ControllerSingleton::GetInstance().UploadCave(filepath);

      ui_->cave_rows->setValue(
          s21::ControllerSingleton::GetInstance().GetCaveRows());
      ui_->cave_cols->setValue(
          s21::ControllerSingleton::GetInstance().GetCaveCols());
    } catch (const std::exception& e) {
      ShowErrorMessage(e);
    }
  }

  ui_->cave_canvas->update();
}

void MainWindow::CaveInitRandomButtonClicked() {
  try {
    s21::ControllerSingleton::GetInstance().GenerateCave(
        ui_->cave_rows->value(), ui_->cave_cols->value(),
        static_cast<float>(ui_->cave_cell_chance->value()));

  } catch (const std::exception& e) {
    ShowErrorMessage(e);
  }

  ui_->cave_canvas->update();
}

void MainWindow::CaveStepRenderButtonClicked() {
  s21::ControllerSingleton::GetInstance().StepRender(
      static_cast<unsigned>(ui_->cave_die_limit_input->value()),
      static_cast<unsigned>(ui_->cave_born_limit_input->value()));

  ui_->cave_canvas->update();
}

void MainWindow::CaveAutoRenderButtonClicked() {
  ui_->cave_auto_render_btn->setEnabled(false);
  emergency_stop_ = false;

  int interval = ui_->cave_render_timeout_input->value();

  timer_->setInterval(interval);
  timer_->start(interval);
}

void MainWindow::CaveStopRenderButtonClicked() { emergency_stop_ = true; }

void MainWindow::TimerCallback() {
  unsigned die_limit =
      static_cast<unsigned>(ui_->cave_die_limit_input->value());
  unsigned born_limit =
      static_cast<unsigned>(ui_->cave_born_limit_input->value());

  bool stop =
      s21::ControllerSingleton::GetInstance().StepRender(die_limit, born_limit);

  if (stop || emergency_stop_) {
    timer_->stop();
    ui_->cave_auto_render_btn->setEnabled(true);
  } else {
    ui_->cave_canvas->update();
  }
}

void MainWindow::ShowErrorMessage(const std::exception& e) {
  QMessageBox::critical(this, "Error", "Error occured: " + QString(e.what()));
}
