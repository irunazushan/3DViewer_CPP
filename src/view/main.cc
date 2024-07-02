#include <QApplication>

#include "viever.h"

using namespace s21;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Viever w;
  w.show();
  return a.exec();
}
