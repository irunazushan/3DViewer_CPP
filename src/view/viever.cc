#include "viever.h"

#include "ui_viever.h"

using namespace s21;

Viever::Viever(QWidget *parent) : QMainWindow(parent), ui(new Ui::Viever) {
  ui->setupUi(this);
  this->setFixedWidth(this->width());
  this->setFixedHeight(this->height());
  set_settings();
  ui->openGLWidget->show();
  connect(ui->pushButton_figure_color, SIGNAL(clicked()), this,
          SLOT(set_figure_color()));
  connect(ui->pushButton_background_color, SIGNAL(clicked()), this,
          SLOT(set_background_color()));
}

Viever::~Viever() { delete ui; }

void Viever::set_figure_color() {
  QString str{};
  if (set_color(&ui->openGLWidget->figure_color, &str)) {
    ui->pushButton_figure_color->setStyleSheet(str);
    ui->openGLWidget->update();
    change_settings();
  }
}

void Viever::set_background_color() {
  QString str{};
  if (set_color(&ui->openGLWidget->background_color, &str)) {
    ui->pushButton_background_color->setStyleSheet(str);
    ui->openGLWidget->update();
    change_settings();
  }
}

int Viever::set_color(struct color *color, QString *str) {
  int result = 0;
  QColor tmp{0, 0, 0};
  tmp = QColorDialog::getColor(tmp);
  color->red = tmp.red();
  color->green = tmp.green();
  color->blue = tmp.blue();
  set_button_color(*color, str);
  result = 1;
  return result;
}

void Viever::set_button_color(struct color color, QString *str) {
  *str = "background-color: rgb(";
  str->append(QString::number(color.red).append(",").append(
      QString::number(color.green)
          .append(",")
          .append(QString::number(color.blue))
          .append(")")));
}

void Viever::on_radioButton_central_pressed() {
  ui->openGLWidget->projection = 0;
  ui->openGLWidget->update();
  change_settings();
}

void Viever::on_radioButton_parallel_pressed() {
  ui->openGLWidget->projection = 1;
  ui->openGLWidget->update();
  change_settings();
}

void Viever::on_radioButton_solid_pressed() {
  ui->openGLWidget->edges = 0;
  ui->openGLWidget->update();
  change_settings();
}

void Viever::on_radioButton_dashed_pressed() {
  ui->openGLWidget->edges = 1;
  ui->openGLWidget->update();
  change_settings();
}

void Viever::on_radioButton_none_pressed() {
  ui->openGLWidget->vertexes = 0;
  ui->openGLWidget->update();
  change_settings();
}

void Viever::on_radioButton_circle_pressed() {
  ui->openGLWidget->vertexes = 1;
  ui->openGLWidget->update();
  change_settings();
}

void Viever::on_radioButton_square_pressed() {
  ui->openGLWidget->vertexes = 2;
  ui->openGLWidget->update();
  change_settings();
}

void Viever::on_pushButton_apply_changes_clicked() {
  if (ui->openGLWidget->vertexes_.size()) {
    m_controller.moveFigure_c(ui->doubleSpinBox_move_x->value(),
                              ui->doubleSpinBox_move_y->value(),
                              ui->doubleSpinBox_move_z->value());
    m_controller.rotateFigure_c(ui->doubleSpinBox_rotate_x->value(),
                                ui->doubleSpinBox_rotate_y->value(),
                                ui->doubleSpinBox_rotate_z->value());
    m_controller.changeFigure_c(ui->doubleSpinBox_scale->value());
    ui->openGLWidget->vertexes_ = m_controller.getVertexes_c();
    ui->openGLWidget->update();
  }
}

void Viever::on_pushButton_open_choose_file_clicked() {
  QString filename1 = QFileDialog::getOpenFileName(0, "Открыть object file",
                                                   "../src/Object_files");
  ui->openGLWidget->filename = qPrintable(filename1);
  try {
    m_controller.setFilename_c(ui->openGLWidget->filename);
    ui->openGLWidget->vertexes_ = m_controller.getVertexes_c();
    ui->openGLWidget->polygons = m_controller.getPolygon_c();
    clean_changes();
    ui->label_open_result->setText("OK");
    std::string tmp = ui->openGLWidget->filename;
    int flag = 1;
    while (flag) {
      int n = tmp.find("/");
      if (n >= 0) {
        for (int i = 0; i <= n; i++) {
          tmp.erase(0, 1);
        }
      } else
        flag = 0;
    }
    ui->filename->setText(QString::fromStdString(tmp));
    ui->vertexes_amount->setText(
        QString::number(ui->openGLWidget->vertexes_.size() / 3));
    ui->edges_amount_2->setText(
        QString::number(m_controller.getFacetsCount() / 2));
  } catch (std::string error_message) {
    ui->label_open_result->setText(QString::fromStdString(error_message));
    ui->openGLWidget->vertexes_.clear();
    ui->openGLWidget->polygons.clear();
    ui->filename->setText("");
    ui->vertexes_amount->setText("");
    ui->openGLWidget->filename = "";
    ui->edges_amount_2->setText("");
  }
  ui->openGLWidget->update();
}

void Viever::on_pushButton_exit_clicked() {
  close();
  ui->openGLWidget->close();
}

void Viever::on_pushButton_clear_changes_clicked() {
  if (ui->label_open_result->text() == "OK") {
    m_controller.setFilename_c(ui->openGLWidget->filename);
    ui->openGLWidget->vertexes_ = m_controller.getVertexes_c();
    ui->openGLWidget->polygons = m_controller.getPolygon_c();
    clean_changes();
    ui->openGLWidget->update();
  }
}

void Viever::clean_changes() {
  ui->doubleSpinBox_move_x->setValue(0);
  ui->doubleSpinBox_move_y->setValue(0);
  ui->doubleSpinBox_move_z->setValue(0);
  ui->doubleSpinBox_rotate_x->setValue(0);
  ui->doubleSpinBox_rotate_y->setValue(0);
  ui->doubleSpinBox_rotate_z->setValue(0);
  ui->doubleSpinBox_scale->setValue(1);
  change_settings();
}

void Viever::on_doubleSpinBox_thikness_valueChanged(double arg1) {
  ui->openGLWidget->thickness = arg1;
  ui->openGLWidget->update();
  change_settings();
}

void Viever::on_pushButton_bmp_clicked() {
  QFileDialog file_dailog(this);
  QDateTime date = QDateTime::currentDateTime();
  QString file_name = "Viewer_" + date.toString("yyyy.MM.dd_hh.mm.ss") + ".bmp";
  QString file_dialog_file_name = file_dailog.getSaveFileName(
      this, tr("Save image"), file_name, tr("image (*.bmp)"));
  QImage image = ui->openGLWidget->grabFramebuffer();
  image.save(file_name);
}

void Viever::on_pushButton_jpeg_clicked() {
  QFileDialog file_dailog(this);
  QDateTime date = QDateTime::currentDateTime();
  QString file_name =
      "Viewer_" + date.toString("yyyy.MM.dd_hh.mm.ss") + ".jpeg";
  QString file_dialog_file_name = file_dailog.getSaveFileName(
      this, tr("Save image"), file_name, tr("image (*.jpeg)"));
  QImage image = ui->openGLWidget->grabFramebuffer();
  image.save(file_name);
}

void Viever::on_pushButton_gif_clicked() {
  gif = new QGifImage(QSize(1000, 1000));
  timerGif = new QTimer(this);
  connect(timerGif, &QTimer::timeout, this, &Viever::gifSelect);

  timerGif->setInterval(100);
  timerGif->start();
}

void Viever::gifSelect() {
  QImage image(640, 480, QImage::Format_RGB32);
  image = ui->openGLWidget->grabFramebuffer();
  gif->addFrame(image, 10);
  fps++;
  ui->pushButton_gif->setText(QString::number(5 - fps / 10));
  if (fps == 50) {
    QString fileName = QFileDialog::getSaveFileName(this, "Gif", "", "(*.gif)");
    timerGif->stop();
    gif->save(fileName);
    QFileInfo check_file(fileName);
    if (check_file.exists())
      QMessageBox::information(NULL, QObject::tr("OK"), tr("Success"));
    else
      QMessageBox::critical(NULL, QObject::tr("Error"), tr("Failed"));
    fps = 0;
    ui->pushButton_gif->setText("GIF");
    delete gif;
    delete timerGif;
  }
}

void Viever::change_settings() {
  QSettings settings("../src/settings.ini", QSettings::IniFormat);
  settings.beginGroup("Settings");
  settings.setValue("ui->openGLWidget->figure_color.red = ",
                    ui->openGLWidget->figure_color.red);
  settings.setValue("ui->openGLWidget->figure_color.green = ",
                    ui->openGLWidget->figure_color.green);
  settings.setValue("ui->openGLWidget->figure_color.blue = ",
                    ui->openGLWidget->figure_color.blue);
  settings.setValue("ui->openGLWidget->background_color.red = ",
                    ui->openGLWidget->background_color.red);
  settings.setValue("ui->openGLWidget->background_color.green = ",
                    ui->openGLWidget->background_color.green);
  settings.setValue("ui->openGLWidget->background_color.blue = ",
                    ui->openGLWidget->background_color.blue);
  settings.setValue("edges = ", ui->openGLWidget->edges);
  settings.setValue("projection = ", ui->openGLWidget->projection);
  settings.setValue("vertexes = ", ui->openGLWidget->vertexes);
  settings.setValue("thickness = ", ui->openGLWidget->thickness);
  settings.endGroup();
}

void Viever::set_settings() {
  QSettings settings("../src/settings.ini", QSettings::IniFormat);
  settings.beginGroup("Settings");
  ui->openGLWidget->figure_color.red =
      settings.value("ui->openGLWidget->figure_color.red = ").toInt();
  ui->openGLWidget->figure_color.green =
      settings.value("ui->openGLWidget->figure_color.green = ").toInt();
  ui->openGLWidget->figure_color.blue =
      settings.value("ui->openGLWidget->figure_color.blue = ").toInt();
  ui->openGLWidget->background_color.red =
      settings.value("ui->openGLWidget->background_color.red = ").toInt();
  ui->openGLWidget->background_color.green =
      settings.value("ui->openGLWidget->background_color.green = ").toInt();
  ui->openGLWidget->background_color.blue =
      settings.value("ui->openGLWidget->background_color.blue = ").toInt();
  QString figure_button_color, background_button_color;
  set_button_color(ui->openGLWidget->figure_color, &figure_button_color);
  set_button_color(ui->openGLWidget->background_color,
                   &background_button_color);
  ui->pushButton_background_color->setStyleSheet(background_button_color);
  ui->pushButton_figure_color->setStyleSheet(figure_button_color);
  ui->openGLWidget->edges = settings.value("edges = ").toInt();
  ui->openGLWidget->projection = settings.value("projection = ").toInt();
  ui->openGLWidget->vertexes = settings.value("vertexes = ").toInt();
  ui->openGLWidget->thickness = settings.value("thickness = ").toDouble();
  if (ui->openGLWidget->edges == 0) ui->radioButton_solid->setChecked(true);
  if (ui->openGLWidget->edges == 1) ui->radioButton_dashed->setChecked(true);
  if (ui->openGLWidget->vertexes == 0) ui->radioButton_none->setChecked(true);
  if (ui->openGLWidget->vertexes == 1) ui->radioButton_circle->setChecked(true);
  if (ui->openGLWidget->vertexes == 2) ui->radioButton_square->setChecked(true);
  if (ui->openGLWidget->projection == 0)
    ui->radioButton_central->setChecked(true);
  if (ui->openGLWidget->projection == 1)
    ui->radioButton_parallel->setChecked(true);
  ui->doubleSpinBox_thikness->setValue(ui->openGLWidget->thickness);
  settings.endGroup();
}
