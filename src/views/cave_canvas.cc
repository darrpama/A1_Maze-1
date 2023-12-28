#include "cave_canvas.h"

void CaveCanvas::paintEvent(QPaintEvent *event) {
  
  cave_ = s21::ControllerSingleton::GetInstance().GetCave();
  
  if (cave_->GetCols() > 0 && cave_->GetRows() > 0) {
    QPainter painter = QPainter(this);
    setFixedSize(500, 500);

    int cols = cave_->GetCols();
    int rows = cave_->GetRows();

    cell_width_ = std::round(500.0f / cols);
    cell_height_ = std::round(500.0f / rows);

    size_t index = 0;
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        unsigned cell = cave_->GetMatrix()[index];
        DrawCell(&painter, i, j, cell);
        index++;
      }
    }
    painter.fillRect(0, 0, 500, 2, Qt::black);
    painter.fillRect(0, 0, 2, 500, Qt::black);
    painter.end();
  }
}

void CaveCanvas::DrawCell(QPainter *p, size_t i, size_t j, unsigned cell) {
  if (cell == 0) {
    DrawCellBody(p, i, j, Qt::GlobalColor::white);
  } else {
    DrawCellBody(p, i, j, Qt::GlobalColor::black);
  }
}

void CaveCanvas::DrawCellBody(QPainter *p, size_t i, size_t j, Qt::GlobalColor color) {
  p->fillRect(
    (cell_width_ * j),
    (cell_height_ * i),
    cell_width_,
    cell_height_, 
    color
  );
}

