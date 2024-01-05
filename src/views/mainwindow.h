#ifndef CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAINWINDOW_H
#define CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAINWINDOW_H

#define GL_SILENCE_DEPRECATION

#include <QApplication>
#include <QFileDialog>
#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QtOpenGL>
#include <QtOpenGLWidgets>

#include "../controllers/controller_singleton.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void MazeUploadButtonClicked();
  void MazeDownloadButtonClicked();
  void MazeInitRandomButtonClicked();
  void CaveUploadButtonClicked();
  void CaveInitRandomButtonClicked();
  void CaveStepRenderButtonClicked();
  void CaveAutoRenderButtonClicked();
  void CaveStopRenderButtonClicked();

 private:
  Ui::MainWindow *ui_;
  QTimer* timer_;
  bool emergency_stop_;

  void ShowErrorMessage(const std::exception &);
};

#endif  // CPP4_3DVIEWER_V2_0_2_SRC_VIEWS_MAINWINDOW_H
