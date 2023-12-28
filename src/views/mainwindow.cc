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
    try
    {
      std::string filepath = file_path.toStdString();
      s21::ControllerSingleton::GetInstance().UploadMaze(filepath);
    }
    catch(const std::exception& e)
    {
      ShowErrorMessage(e);
    }
  }
}

void MainWindow::on_generate_btn_clicked() {
  try
  {
    s21::ControllerSingleton::GetInstance().GenerateMaze(ui_->rows_input->value(), ui_->cols_input->value());
  }
  catch(const std::exception& e)
  {
    ShowErrorMessage(e);
  }
  
  ui_->maze_canvas->update();
}

void MainWindow::on_cave_upload_btn_clicked() {
  QString file_path = QFileDialog::getOpenFileName(
    this, tr("Select File"), "", tr("All Files (*.*)")
  );
  if (!file_path.isEmpty()) {
    try
    {
      std::string filepath = file_path.toStdString();
      s21::ControllerSingleton::GetInstance().UploadCave(filepath);
    }
    catch(const std::exception& e)
    {
      ShowErrorMessage(e);
    }
  }
}

void MainWindow::on_cave_init_random_btn_clicked() {
  try
  {
    s21::ControllerSingleton::GetInstance().GenerateCave(
      static_cast<unsigned>(ui_->cave_rows->value()),
      static_cast<unsigned>(ui_->cave_cols->value()),
      static_cast<float>(ui_->cave_cell_chance->value())
    );
  }
  catch(const std::exception& e)
  {
    ShowErrorMessage(e);
  }
  ui_->cave_canvas->update();
}

void MainWindow::on_step_render_btn_clicked() {
  s21::ControllerSingleton::GetInstance().StepRender(
    static_cast<unsigned>(ui_->die_limit_input->value()),
    static_cast<unsigned>(ui_->born_limit_input->value())
  );
  ui_->cave_canvas->update();
}

void MainWindow::ShowErrorMessage(const std::exception& e) {
    std::cerr << e.what() << '\n';
    QMessageBox messageBox;
    messageBox.critical(0,"Error",e.what());
    messageBox.setFixedSize(500,200);
}

void MainWindow::on_auto_render_btn_clicked() {
  QTimer* timer = new QTimer(this);
  int interval = ui_->render_timeout_input->value();

  unsigned die_limit = static_cast<unsigned>(ui_->die_limit_input->value());
  unsigned born_limit = static_cast<unsigned>(ui_->born_limit_input->value());

  // connect(timer, &QTimer::timeout, this, [die_limit, born_limit, &cave_canvas = ui_->cave_canvas]() {
  connect(timer, &QTimer::timeout, this, [timer, die_limit, born_limit, &cave_canvas = ui_->cave_canvas]() {
    bool stop = s21::ControllerSingleton::GetInstance().StepRender(die_limit, born_limit);
    if (stop) {
      std::cout << "auto render stoped" << std::endl;
      timer->stop();
    } else {
      cave_canvas->update();
    }
    // code bellow is not work. Why??
  });

  timer->start(interval);
}

