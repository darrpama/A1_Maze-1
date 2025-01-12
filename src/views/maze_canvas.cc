#include "maze_canvas.h"

MazeCanvas::MazeCanvas(QWidget *parent)
    : QWidget(parent),
      kBorderSize(2.0f),
      border_color_(QColor(170, 170, 170)),
      frame_color_(QColor(170, 170, 170)),
      line_color_(QColor(204, 0, 0)),
      background_color_(QColor(255, 255, 255)) {
  painter_ = nullptr;

  cell_width_ = 0.0f;
  cell_height_ = 0.0f;
  cols_ = 0;
  rows_ = 0;
  click_counter_ = 0;
}

MazeCanvas::~MazeCanvas() {
  if (painter_) {
    delete painter_;
  }
}

void MazeCanvas::ClearPath(int rows, int cols) {
  if (cols_ != cols || rows_ != rows) {
    click_counter_ = 0;
    path_cells_.clear();
  }
}

void MazeCanvas::mousePressEvent(QMouseEvent *event) {
  if (click_counter_ < 2) {
    click_counter_ += 1;
    int x = event->position().x();
    int y = event->position().y();
    int row = y / (cell_height_ + 2);
    int col = x / (cell_width_ + 2);
    path_cells_.push_back(s21::Vector2D(row, col));
  } else {
    click_counter_ = 0;
    path_cells_.clear();
  }
  update();
}

void MazeCanvas::paintEvent(QPaintEvent *) {
  matrix_ = s21::ControllerSingleton::GetInstance().GetMazeMatrix();
  cols_ = s21::ControllerSingleton::GetInstance().GetMazeCols();
  rows_ = s21::ControllerSingleton::GetInstance().GetMazeRows();

  float width = this->width();
  float height = this->height();

  cell_width_ = (static_cast<float>(width) / cols_) - kBorderSize;
  cell_height_ = (static_cast<float>(height) / rows_) - kBorderSize;

  if (cols_ > 0 && rows_ > 0) {
    if (painter_) {
      delete painter_;
      painter_ = nullptr;
    }

    painter_ = new QPainter(this);
    DrawBackground();
    DrawMaze();
    DrawPath();
    DrawFrames();
    painter_->end();
  }
}

void MazeCanvas::DrawMaze() {
  setFixedSize(width(), height());
  size_t index = 0;

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
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

void MazeCanvas::DrawBackground() {
  painter_->fillRect(0, 0, width(), height(), background_color_);
}
void MazeCanvas::DrawFrames() {
  painter_->fillRect(0, 0, width(), kBorderSize, frame_color_);
  painter_->fillRect(0, 0, kBorderSize, height(), frame_color_);
  painter_->fillRect(width() - kBorderSize, 0, kBorderSize, height(),
                     frame_color_);
  painter_->fillRect(0, height() - kBorderSize, width(), kBorderSize,
                     frame_color_);
}

void MazeCanvas::DrawClickedCellBody() {
  for (auto cell : path_cells_) {
    painter_->fillRect((cell_width_ * cell.y_) + (cell.y_ * 2),
                       (cell_height_ * cell.x_) + (cell.x_ * 2), cell_width_,
                       cell_height_, Qt::GlobalColor::yellow);
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
  painter_->fillRect((cell_width_ * j) + (j * 2), (cell_height_ * i) + (i * 2),
                     cell_width_, cell_height_, Qt::GlobalColor::white);
}

void MazeCanvas::DrawRightBorder(size_t i, size_t j) {
  painter_->fillRect(((cell_width_ * j) + (j * 2) + cell_width_),
                     ((cell_height_ * i) + (i * 2)) - 2, 2, cell_height_ + 4,
                     border_color_);
}

void MazeCanvas::DrawBottomBorder(size_t i, size_t j) {
  painter_->fillRect((cell_width_ * j) + (j * 2) - 2,
                     (cell_height_ * i) + (i * 2) + cell_height_,
                     cell_width_ + 4, 2, border_color_);
}

void MazeCanvas::DrawLineBetweenCellsCenters(s21::Vector2D src,
                                             s21::Vector2D dst) {
  QPen pen(line_color_, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
  painter_->setPen(pen);

  painter_->drawLine(
      (cell_width_ * src.y_) + (cell_width_ / 2) + (src.y_ * 2),
      (cell_height_ * src.x_) + (cell_height_ / 2) + (src.x_ * 2),
      (cell_width_ * dst.y_) + (cell_width_ / 2) + (dst.y_ * 2),
      (cell_height_ * dst.x_) + (cell_height_ / 2) + (dst.x_ * 2));
}

void MazeCanvas::DrawPathLine() {
  std::vector<s21::Vector2D> path =
      s21::ControllerSingleton::GetInstance().ResolveMaze(path_cells_[0],
                                                          path_cells_[1]);
  for (size_t i = 0; i < path.size() - 1; i++) {
    DrawLineBetweenCellsCenters(path[i], path[i + 1]);
  }
}
