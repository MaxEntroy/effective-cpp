#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "shape.h"

class Circle : public Shape {
 public:
  Circle() {}
  explicit Circle(double r) : radius_(r) {}

 public:
  double GetArea() const override;
  std::string NameOf() const override;

 private:
  double radius_;
};

#endif
