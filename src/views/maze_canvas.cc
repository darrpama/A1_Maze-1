#include "maze_canvas.h"

MazeCanvas::MazeCanvas(QWidget *parent) : QWidget(parent) {}

void MazeCanvas::mousePressEvent(QMouseEvent *event) {
  if (click_counter_ < 2) {
    click_counter_ += 1;
    int x = event->position().x();
    int y = event->position().y();
    int row = y / (cell_width_ + 2);
    int col = x / (cell_height_ + 2);
    path_cells_.push_back(s21::Vector2D(row, col));
  } else {
    click_counter_ = 0;
    path_cells_.clear();
  }
  update();
}

void MazeCanvas::paintEvent(QPaintEvent *event) {
  matrix_ = s21::ControllerSingleton::GetInstance().GetMazeMatrix();
  cols_ = s21::ControllerSingleton::GetInstance().GetMazeCols();
  rows_ = s21::ControllerSingleton::GetInstance().GetMazeRows();

  width_ = 500;
  height_ = 500;
  border_size_ = 2.0f;

  cell_width_ = (static_cast<float>(width_) / cols_) - border_size_;
  cell_height_ = (static_cast<float>(height_) / rows_) - border_size_;
  
  painter_ = new QPainter(this);

  if (cols_ > 0 && rows_ > 0) {
    DrawMaze();
    DrawPath();
    DrawFrames();
  }
  painter_->end();
}

void MazeCanvas::DrawMaze() {
  setFixedSize(width_, height_);
  size_t index = 0;

  for (size_t i = 0; i < rows_; i++) {
    for (size_t j = 0; j < cols_; j++) {
      s21::Border border = matrix_[index];
      DrawCell(i, j, border);
      index++;
    }
  }
}

void MazeCanvas::DrawPath() {
  if (click_counter_ > 0) {
    DrawClickedCellBody();
  }
  if (click_counter_ == 2) {
    DrawPathLine();
  }
}

void MazeCanvas::DrawFrames() {
  painter_->fillRect(0, 0, 500, 2, Qt::black);
  painter_->fillRect(0, 0, 2, 500, Qt::black);
  painter_->fillRect(498, 0, 2, 500, Qt::black);
  painter_->fillRect(0, 498, 500, 2, Qt::black);
}

void MazeCanvas::DrawClickedCellBody() {
  for (auto cell : path_cells_) {
    painter_->fillRect(
      (cell_width_ * cell.y_) + (cell.y_*2),
      (cell_height_ * cell.x_) + (cell.x_*2),
      cell_width_,
      cell_height_, 
      Qt::GlobalColor::yellow
    );
  }
}

void MazeCanvas::DrawCell(size_t i, size_t j, s21::Border border) {
  DrawCellBody(i, j);
  if (border == s21::Border::RIGHT_BORDER) {
    DrawRightBorder(i, j);
  }
  if (border == s21::Border::BOTTOM_BORDER) {
    DrawBottomBorder(i, j);
  }
  if (border == s21::Border::BOTH_BORDER) {
    DrawRightBorder(i, j);
    DrawBottomBorder(i, j);
  }
}

void MazeCanvas::DrawCellBody(size_t i, size_t j) {
  painter_->fillRect(
    (cell_width_ * j) + (j*2),
    (cell_height_ * i) + (i*2),
    cell_width_,
    cell_height_, 
    Qt::GlobalColor::white
  );
}

void MazeCanvas::DrawRightBorder(size_t i, size_t j) {
  painter_->fillRect(
    (cell_width_ * j) + (j*2) + cell_width_,
    (cell_height_ * i) + (i*2),
    2,
    cell_height_,
    Qt::GlobalColor::darkBlue
  );
}

void MazeCanvas::DrawBottomBorder(size_t i, size_t j) {
  painter_->fillRect(
    (cell_width_ * j) + (j*2),
    (cell_height_ * i) + (i*2) + cell_height_,
    cell_width_,
    2,
    Qt::GlobalColor::darkBlue
  );
}

void MazeCanvas::DrawLineBetweenCellsCenters(s21::Vector2D a, s21::Vector2D b) {
  painter_->drawLine(
    (cell_height_ * a.y_) + (cell_height_ / 2) + (a.y_ * 2),
    (cell_width_ * a.x_) + (cell_width_ / 2) + (a.x_ * 2),
    (cell_height_ * b.y_) + (cell_height_ / 2) + (b.y_ * 2),
    (cell_width_ * b.x_) + (cell_width_ / 2) + (b.x_ * 2)
  );
}

void MazeCanvas::DrawPathLine() {
  std::vector<s21::Vector2D> path = s21::ControllerSingleton::GetInstance().ResolveMaze(path_cells_[0], path_cells_[1]);
  for (int i = 0; i < path.size() - 1; i++) {
    DrawLineBetweenCellsCenters(path[i], path[i+1]);
  }
}