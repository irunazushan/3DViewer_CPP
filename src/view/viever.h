#ifndef VIEVER_H
#define VIEVER_H

#include <GL/gl.h>

#include <QColorDialog>
#include <QFileDialog>
#include <QImage>
#include <QMainWindow>
#include <QMessageBox>
#include <QMovie>
#include <QSettings>
#include <iostream>

#include "../controller/controller.h"
#include "glview.h"
#include "qgifimage/gifimage/qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Viever;
}
QT_END_NAMESPACE

namespace s21 {

class Viever : public QMainWindow {
  Q_OBJECT

 public:
  Viever(QWidget *parent = nullptr);
  ~Viever();
  void clean_changes();
  void set_settings();

 private slots:
  void set_figure_color();
  void set_background_color();
  int set_color(struct color *color, QString *str);
  void set_button_color(struct color color, QString *str);
  void on_radioButton_central_pressed();
  void on_radioButton_parallel_pressed();
  void on_radioButton_solid_pressed();
  void on_radioButton_dashed_pressed();
  void on_radioButton_none_pressed();
  void on_radioButton_circle_pressed();
  void on_radioButton_square_pressed();
  void on_pushButton_apply_changes_clicked();
  void on_pushButton_open_choose_file_clicked();
  void on_pushButton_exit_clicked();
  void on_pushButton_clear_changes_clicked();
  void on_doubleSpinBox_thikness_valueChanged(double arg1);
  void on_pushButton_bmp_clicked();
  void on_pushButton_jpeg_clicked();
  void on_pushButton_gif_clicked();
  void change_settings();
  void gifSelect();

 private:
  Ui::Viever *ui;
  Controller m_controller;

  QTimer *timerGif;
  QGifImage *gif;
  int fps = 0;
};

}  // namespace s21
#endif  // VIEVER_H
