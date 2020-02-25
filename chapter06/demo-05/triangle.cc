#include "triangle.h"

double Triangle::GetArea() const {
  return 1.0 / 2 * length_ * height_;
}

std::string Triangle::NameOf() const {
  return "This is a triangle.";
}
