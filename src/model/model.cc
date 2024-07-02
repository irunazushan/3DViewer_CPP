#include "model.h"

using namespace s21;

void Model::polygonBuild(std::string buffer) {
  setlocale(LC_NUMERIC, "C");
  polygon_t tmp{};
  while (buffer.size()) {
    while (buffer.size() && !(isdigit(buffer[0])) && buffer[0] != '-')
      buffer.erase(0, 1);
    if (buffer.size()) {
      int value = stod(buffer);
      if (value < 0) value = vertexes.size() / 3 + value + 1;
      (tmp.polygon_vertexes).push_back(value);
      (tmp.numbers_of_vertexes_in_facets)++;
    }
    while (buffer.size() && buffer[0] != ' ') buffer.erase(0, 1);
  }
  if (tmp.numbers_of_vertexes_in_facets < 3)
    throw std::string{"ERROR: Too few vertexes in the polygon!"};
  facets += tmp.numbers_of_vertexes_in_facets;
  polygon_.push_back(tmp);
}

void Model::centerFigure() {
  double x_max = vertexes[0];
  double x_min = vertexes[0];
  double y_max = vertexes[1];
  double y_min = vertexes[1];
  double z_max = vertexes[2];
  double z_min = vertexes[2];
  for (auto it = vertexes.begin(); it != vertexes.end();) {
    if (*it > x_max) x_max = *it;
    if (*it < x_min) x_min = *it;
    it++;
    if (*it > y_max) y_max = *it;
    if (*it < y_min) y_min = *it;
    it++;
    if (*it > z_max) z_max = *it;
    if (*it < z_min) z_min = *it;
    it++;
  }
  double center_x = (x_max + x_min) / 2;
  double center_y = (y_max + y_min) / 2;
  double center_z = (z_max + z_min) / 2;
  for (auto it = vertexes.begin(); it != vertexes.end();) {
    *it -= center_x;
    it++;
    *it -= center_y;
    it++;
    *it -= center_z;
    it++;
  }
}

int Model::getFacets() { return facets; }

void Model::changeFigure(double n) {
  int i = 1;
  for (auto it = vertexes.begin(); it != vertexes.end(); it++, i++) {
    if (i == 1) *it *= n;
    if (i == 2) *it *= n;
    if (i == 3) {
      *it *= n;
      i = 0;
    }
  }
}

std::vector<double> Model::getVertexes() { return vertexes; }

std::vector<polygon_t> Model::getPolygon() { return polygon_; }