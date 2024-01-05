#include "cave_canvas.h"

CaveCanvas::CaveCanvas(QWidget *parent) : QWidget(parent) {
  painter_ = nullptr;
}

CaveCanvas::~CaveCanvas() {
  if (painter_) {
    delete painter_;
  }
}

void CaveCanvas::paintEvent(QPaintEvent *event) {
  matrix_ = s21::ControllerSingleton::GetInstance().GetCaveMatrix();
  cols_ = s21::ControllerSingleton::GetInstance().GetCaveCols();
  rows_ = s21::ControllerSingleton::GetInstance().GetCaveRows();
  width_ = 500.0f;
  height_ = 500.0f;
  border_size_ = 2.0f;

  cell_width_ = width_ / static_cast<float>(cols_);
  cell_height_ = height_ / static_cast<float>(rows_);

  if (cols_ > 0 && rows_ > 0) {
    if (painter_) {
      delete painter_;
      painter_ = nullptr;
    }
    painter_ = new QPainter(this);
    DrawCave();
    DrawFrames();
    painter_->end();
  }
}

void CaveCanvas::DrawCave() {
  setFixedSize(width_, height_);
  size_t index = 0;
  for (size_t i = 0; i < rows_; i++) {
    for (size_t j = 0; j < cols_; j++) {
      DrawCell(i, j, matrix_[index]);
      index++;
    }
  }
}

void CaveCanvas::DrawFrames() {
  painter_->fillRect(0, 0, width_, border_size_, Qt::black);
  painter_->fillRect(0, 0, border_size_, height_, Qt::black);
  painter_->fillRect((width_ - border_size_), 0, border_size_, height_,
                     Qt::black);
  painter_->fillRect(0, (height_ - border_size_), width_, border_size_,
                     Qt::black);
}

void CaveCanvas::DrawCell(size_t i, size_t j, unsigned cell) {
  painter_->fillRect(
      (cell_width_ * static_cast<float>(j)),
      (cell_height_ * static_cast<float>(i)), cell_width_, cell_height_,
      (cell == 0) ? Qt::GlobalColor::white : Qt::GlobalColor::black);
}
