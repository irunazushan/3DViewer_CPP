#include "model.h"

namespace s21 {

Model &Model::initModel() {
  static Model theModelObject;
  return theModelObject;
}

void Model::setFilename(std::string filename) {
  vertexes.clear();
  polygon_.clear();
  facets = 0;
  if (filename.find(".obj") == std::string::npos)
    throw std::string{"ERROR: The file has a wrong format"};
  std::string buffer;
  std::ifstream in(filename);
  if (in.is_open()) {
    while (std::getline(in, buffer)) {
      if (buffer.size() > 2) {
        if (buffer[0] == 'v' && buffer[1] == ' ') vertexParsing(buffer);
        if (buffer[0] == 'f' && buffer[1] == ' ') polygonBuild(buffer);
      }
    }
    in.close();
  } else
    throw std::string{"ERROR: The file doesn't exist!"};
  if (vertexes.size() < 12) throw std::string{"ERROR: Too few vertexes!"};
  if (polygon_.size() < 4) throw std::string{"ERROR: Too few facets!"};
  centerFigure();
}

void Model::vertexParsing(std::string buffer) {
  setlocale(LC_NUMERIC, "C");
  int tmp_count = vertexes.size();
  while (buffer.size()) {
    while (buffer.size() && !(isdigit(buffer[0])) && buffer[0] != '-')
      buffer.erase(0, 1);
    if (buffer.size()) vertexes.push_back(stod(buffer));
    while (buffer.size() && buffer[0] != ' ') buffer.erase(0, 1);
  }
  if (vertexes.size() - tmp_count > 3)
    throw std::string{"ERROR: The wrong vertex data!"};
}

}  // namespace s21