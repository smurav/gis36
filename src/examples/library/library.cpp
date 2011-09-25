#include "library.h"

Library::Library(QObject *parent) : QObject(parent) {
}

int Library::Sum(int a, int b) {
  return a + b;
}
