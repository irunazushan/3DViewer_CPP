#ifndef TRANSFORMER_STRATEGY_H_
#define TRANSFORMER_STRATEGY_H_

#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#define PI 3.141592653589793238462643383279502884L

namespace s21 {

typedef struct facets {
  std::vector<int> polygon_vertexes;
  int numbers_of_vertexes_in_facets;
} polygon_t;

class TransformationStrategy {
 public:
  virtual void transform(std::vector<double>& vertexes, double x = 0,
                         double y = 0, double z = 0) = 0;
  virtual ~TransformationStrategy() {}
};

class MoveFigureStrategy : public TransformationStrategy {
 public:
  void transform(std::vector<double>& vertexes, double x, double y,
                 double z) override;
};

class RotateFigureStrategy : public TransformationStrategy {
 public:
  void transform(std::vector<double>& vertexes, double x, double y,
                 double z) override;
};

}  // namespace s21

#endif