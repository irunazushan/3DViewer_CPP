#ifndef GLVIEW_H
#define GLVIEW_H

#include <GL/gl.h>

#include <QColorDialog>
#include <QFileDialog>
#include <QOpenGLWidget>
#include <QtOpenGL>
#include <iostream>

#include "../controller/controller.h"
#include "viever.h"

using namespace s21;

namespace s21 {

typedef struct color {
  int red;
  int green;
  int blue;
} color;

class glView : public QOpenGLWidget, protected QOpenGLFunctions {
 public:
  explicit glView(QWidget *parent) : QOpenGLWidget(parent) {}

  glView();
  std::string filename{};
  std::vector<double> vertexes_;
  std::vector<polygon_t> polygons;
  color figure_color;
  color background_color;
  int projection;
  int edges;
  int vertexes;
  double thickness;

 protected:
  void initializeGL() override;
  void paintGL() override;
};

}  // namespace s21

#endif  // GLVIEW_H
