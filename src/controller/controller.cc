#include "controller.h"

using namespace s21;

void Controller::setFilename_c(std::string filename) {
  m_model_.setFilename(filename);
}

std::vector<double> Controller::getVertexes_c() {
  return m_model_.getVertexes();
}

std::vector<polygon_t> Controller::getPolygon_c() {
  return m_model_.getPolygon();
}

void Controller::moveFigure_c(double x, double y, double z) {
  m_model_.moveFigure(x, y, z);
}

void Controller::rotateFigure_c(double x, double y, double z) {
  m_model_.rotateFigure(x, y, z);
}

void Controller::changeFigure_c(double n) { m_model_.changeFigure(n); }

int Controller::getFacetsCount() { return m_model_.getFacets(); }
