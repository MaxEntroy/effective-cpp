#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "shape.h"

class Triangle : public Shape {
 public:
  Triangle() {}
  Triangle(double l, double w) : length_(l), height_(w) {}

 public:
  double GetArea() const override;
  std::string NameOf() const override;

 private:
  double length_;
  double height_;
};

#endif
