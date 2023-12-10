#ifndef CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAINWINDOW_H
#define CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAINWINDOW_H

#define GL_SILENCE_DEPRECATION

#include <iostream>

#include <QtOpenGL>
#include <QtOpenGLWidgets>
#include <QApplication>
#include <QMainWindow>
#include <QPainter>
#include <QFileDialog>

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

private slots:
  void on_upload_btn_clicked();
  void on_generate_btn_clicked();
  void on_cave_upload_btn_clicked();
  void on_cave_init_random_btn_clicked();

private:
  Ui::MainWindow *ui_;
};

#endif // CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAINWINDOW_H
