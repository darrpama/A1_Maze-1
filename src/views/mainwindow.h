#ifndef CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAINWINDOW_H
#define CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAINWINDOW_H

#define GL_SILENCE_DEPRECATION

#include <iostream>

#include <QtOpenGL>
#include <QtOpenGLWidgets>
#include <QApplication>
#include <QMainWindow>
#include <QPainter>

#include "../controllers/controller_singleton.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

//  private slots:
  // some slots

private:
  Ui::MainWindow *ui_;
  std::vector<int> maze_;
  int cols_;
  int rows_;
  int cell_width_ = 0;
  int cell_height_ = 0;

  void DrawCell(QPainter *p, size_t i, size_t j, int wall);
  void DrawCellBody(QPainter *p, size_t i, size_t j);
  void DrawRightWall(QPainter *p, size_t i, size_t j);
  void DrawBottomWall(QPainter *p, size_t i, size_t j);
};

#endif // CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAINWINDOW_H
