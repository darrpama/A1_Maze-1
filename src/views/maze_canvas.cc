#include "maze_canvas.h"

void MazeCanvas::mousePressEvent(QMouseEvent *event) {
  if (click_counter_ < 2) {
    click_counter_ += 1;
    int x = event->position().x();
    int y = event->position().y();
    int row = y / (cell_width_ + 2);
    int col = x / (cell_height_ + 2);
    cells_.push_back(std::make_pair(row, col));
  } else {
    click_counter_ = 0;
    cells_.clear();
  }
  update();
}

void MazeCanvas::paintEvent(QPaintEvent *event) {
  maze_ = s21::ControllerSingleton::GetInstance().GetMaze();
  
  if (maze_->GetCols() > 0 && maze_->GetRows() > 0) {
    QPainter painter = QPainter(this);
    setFixedSize(500, 500);

    int cols = maze_->GetCols();
    int rows = maze_->GetRows();

    cell_width_ = std::round(498.0f / cols - 2.0f);
    cell_height_ = std::round(498.0f / rows - 2.0f);

    size_t index = 0;
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        s21::Border border = maze_->GetMatrix()[index];
        DrawCell(&painter, i, j, border);
        index++;
      }
    }

    if (click_counter_ > 0) {
      DrawClickedCellBody(&painter);
    }
    if (click_counter_ == 2) {
      DrawPathLine(&painter);
    }

    painter.fillRect(0, 0, 500, 2, Qt::black);
    painter.fillRect(0, 0, 2, 500, Qt::black);
    painter.end();
  }
}

void MazeCanvas::DrawClickedCellBody(QPainter *p) {
  for (auto cell : cells_) {
    p->fillRect(
      (cell_width_ * cell.second) + (cell.second*2),
      (cell_height_ * cell.first) + (cell.first*2),
      cell_width_,
      cell_height_, 
      Qt::GlobalColor::yellow
    );
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

void MazeCanvas::DrawLineBetweenCellsCenters(QPainter *p, size_t row_1, size_t col_1, size_t row_2, size_t col_2) {
  p->drawLine(
    (cell_height_ * col_1) + (cell_height_ / 2) + (col_1*2),
    (cell_width_ * row_1) + (cell_width_ / 2) + (row_1*2),
    (cell_height_ * col_2) + (cell_height_ / 2) + (col_2*2),
    (cell_width_ * row_2) + (cell_width_ / 2) + (row_2*2)
  );
}

void MazeCanvas::DrawPathLine(QPainter *p) {
  std::vector<std::pair<size_t, size_t>> path = maze_->Resolve(cells_[0], cells_[1]);
  for (int i = 0; i < path.size() - 1; i++) {
    DrawLineBetweenCellsCenters(p, path[i].first, path[i].second, path[i+1].first, path[i+1].second);
  }
}