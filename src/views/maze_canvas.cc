#include "maze_canvas.h"

void MazeCanvas::paintEvent(QPaintEvent *event) {
  maze_ = s21::ControllerSingleton::GetInstance().GetMaze();
  
  if (maze_->GetCols() > 0 && maze_->GetRows() > 0) {
    QPainter painter = QPainter(this);
    setFixedSize(500, 500);

    int cols = maze_->GetCols();
    int rows = maze_->GetRows();

    cell_width_ = 496.0f / cols;
    cell_height_ = 496.0f / rows;

    size_t index = 0;
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        s21::Border border = maze_->GetMatrix()[index];
        DrawCell(&painter, i, j, border);
        index++;
      }
    }
    painter.fillRect(0, 0, 500, 2, Qt::black);
    painter.fillRect(0, 0, 2, 500, Qt::black);
    painter.end();
  }
}

void MazeCanvas::DrawCell(QPainter *p, size_t i, size_t j, s21::Border border) {
  if (border == s21::Border::NO_BORDER) {
    DrawCellBody(p, i, j);
  }
  if (border == s21::Border::RIGHT_BORDER) {
    DrawCellBody(p, i, j);
    DrawRightBorder(p, i, j);
  }
  if (border == s21::Border::BOTTOM_BORDER) {
    DrawCellBody(p, i, j);
    DrawBottomBorder(p, i, j);
  }
  if (border == s21::Border::BOTH_BORDER) {
    DrawCellBody(p, i, j);
    DrawRightBorder(p, i, j);
    DrawBottomBorder(p, i, j);
  }
}

void MazeCanvas::DrawCellBody(QPainter *p, size_t i, size_t j) {
  p->fillRect(
    (cell_width_ * j) + (j*2),
    (cell_height_ * i) + (i*2),
    cell_width_,
    cell_height_, 
    Qt::GlobalColor::white
  );
}

void MazeCanvas::DrawRightBorder(QPainter *p, size_t i, size_t j) {
  p->fillRect(
    (cell_width_ * j) + (j*2) + cell_width_,
    (cell_height_ * i) + (i*2),
    2,
    cell_height_,
    Qt::GlobalColor::darkBlue
  );
}

void MazeCanvas::DrawBottomBorder(QPainter *p, size_t i, size_t j) {
  p->fillRect(
    (cell_width_ * j) + (j*2),
    (cell_height_ * i) + (i*2) + cell_height_,
    cell_width_,
    2,
    Qt::GlobalColor::darkBlue
  );
}

