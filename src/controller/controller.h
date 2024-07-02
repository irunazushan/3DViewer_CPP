#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../model/model.h"

namespace s21 {

class Controller {
 public:
  void setFilename_c(std::string filename);
  std::vector<double> getVertexes_c();
  std::vector<polygon_t> getPolygon_c();
  void moveFigure_c(double x, double y, double z);
  void rotateFigure_c(double x, double y, double z);
  void changeFigure_c(double n);
  void clearChanges_c();
  int getFacetsCount();

 private:
  Model m_model_ = Model::initModel();
};

}  // namespace s21

#endif
