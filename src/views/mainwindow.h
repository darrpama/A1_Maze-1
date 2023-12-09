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

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
>>>>>>> 066d36928eeb69553c293e71c998aba6b41d124b
private slots:
  void on_upload_btn_clicked();
  void on_generate_btn_clicked();
  void on_cave_upload_btn_clicked();

<<<<<<< HEAD
=======
>>>>>>> added cave upload, parse and render;
>>>>>>> 066d36928eeb69553c293e71c998aba6b41d124b
private:
  Ui::MainWindow *ui_;
};

#endif // CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAINWINDOW_H
