#ifndef MODEL_H_
#define MODEL_H_

#include "transformer_strategy.h"

namespace s21 {

class Model {
 public:
  static Model& initModel();
  void setFilename(std::string filename);
  void vertexParsing(std::string buffer);
  void polygonBuild(std::string buffer);
  void centerFigure();
  void moveFigure(double x, double y, double z) {
    setTransformationStrategy(std::make_shared<MoveFigureStrategy>());
    applyTransformation(x, y, z);
  };
  void rotateFigure(double x, double y, double z) {
    setTransformationStrategy(std::make_shared<RotateFigureStrategy>());
    applyTransformation(x, y, z);
  }
  void changeFigure(double n);

  std::vector<double> getVertexes();
  std::vector<polygon_t> getPolygon();
  int getFacets();
  void setTransformationStrategy(
      std::shared_ptr<TransformationStrategy> strategy) {
    transformationStrategy = strategy;
  }
  void applyTransformation(double x = 0, double y = 0, double z = 0) {
    if (transformationStrategy) {
      transformationStrategy->transform(vertexes, x, y, z);
    }
  }

 private:
  std::shared_ptr<TransformationStrategy> transformationStrategy;
  std::vector<polygon_t> polygon_;
  std::vector<double> vertexes;
  int facets;
};
}  // namespace s21
#endif
