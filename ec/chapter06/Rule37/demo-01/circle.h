#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "shape.h"

namespace ec {

class Circle : public Shape {
 public:
   Circle() : radius_(1.0) {}
   explicit Circle(double r) : radius_(r) {}

 public:
   void set_radius(double r) {radius_ = r;}
   double radius() const {return radius_;}

 public:
  std::string NameOf() const override;
  void Draw(Color color = kYellow) const override;

 private:
  double radius_;
};

} // namespace ec


#endif // CIRCLE_H_
