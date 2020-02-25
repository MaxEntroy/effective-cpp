#include "rectangle.h"

double Rectangle::GetArea() const {
  return length_ * width_;
}

std::string Rectangle::NameOf() const {
  return "This is a rectangle.";
}
