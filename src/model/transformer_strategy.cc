#include "transformer_strategy.h"

using namespace s21;

void MoveFigureStrategy::transform(std::vector<double>& vertexes, double x,
                                   double y, double z) {
  for (auto it = vertexes.begin(); it != vertexes.end();) {
    *it += x;
    it++;
    *it += y;
    it++;
    *it += z;
    it++;
  }
}

void RotateFigureStrategy::transform(std::vector<double>& vertexes, double x,
                                     double y, double z) {
  x = x / 180 * PI;
  y = y / 180 * PI;
  z = z / 180 * PI;
  for (auto it = vertexes.begin(); it != vertexes.end(); it = it + 3) {
    if (x != 0) {
      double tmp = *(it + 1);
      *(it + 1) = *(it + 1) * cos(x) - *(it + 2) * sin(x);
      *(it + 2) = tmp * sin(x) + *(it + 2) * cos(x);
    }
    if (y != 0) {
      double tmp = *it;
      *it = *it * cos(y) + *(it + 2) * sin(y);
      *(it + 2) = tmp * (-sin(y)) + *(it + 2) * cos(y);
    }
    if (z != 0) {
      double tmp = *it;
      *it = *it * cos(z) + *(it + 1) * (-sin(z));
      *(it + 1) = tmp * sin(z) + *(it + 1) * cos(z);
    }
  }
}