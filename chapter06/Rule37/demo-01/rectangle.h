#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "shape.h"

namespace ec {

class Rectangle : public Shape {
 public:
  Rectangle() : width_(1.0), length_(1.0) {}
  Rectangle(double w, double l) : width_(w), length_(l) {}

 public:
  void set_width(double w) {width_ = w;}
  double width() const {return width_;}

  void set_length_(double l) {length_ = l;}
  double length() const {return length_;}

 public:
  std::string NameOf() const override;
  void Draw(Color color = kRed) const override;

 private:
  double width_;
  double length_;
};

} // namespace ec

#endif // RECTANGLE_H_
