#include "cave_canvas.h"

void CaveCanvas::paintEvent(QPaintEvent *event) {
  matrix_ = s21::ControllerSingleton::GetInstance().GetCaveMatrix();
  cols_ = s21::ControllerSingleton::GetInstance().GetCaveCols();
  rows_ = s21::ControllerSingleton::GetInstance().GetCaveRows();
  width_ = 500.0f;
  height_ = 500.0f;
  border_size_ = 2.0f;
  cell_width_ = std::round(width_ / cols_);
  cell_height_ = std::round(height_ / rows_);
  
  if (cols_ > 0 && rows_ > 0) {
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
      unsigned cell = matrix_[index];
      DrawCell(i, j, cell);
      index++;
    }
  }
}

void CaveCanvas::DrawFrames() {
  painter_->fillRect(0, 0, width_, border_size_, Qt::black);
  painter_->fillRect(0, 0, border_size_, height_, Qt::black);
  painter_->fillRect((width_ - border_size_), 0, border_size_, height_, Qt::black);
  painter_->fillRect(0, (height_ - border_size_), width_, border_size_, Qt::black);
}

void CaveCanvas::DrawCell(size_t i, size_t j, unsigned cell) {
  if (cell == 0) {
    DrawCellBody(i, j, Qt::GlobalColor::white);
  } else {
    DrawCellBody(i, j, Qt::GlobalColor::black);
  }
}

void CaveCanvas::DrawCellBody(size_t i, size_t j, Qt::GlobalColor color) {
  painter_->fillRect(
    (cell_width_ * j),
    (cell_height_ * i),
    cell_width_,
    cell_height_, 
    color
  );
}

