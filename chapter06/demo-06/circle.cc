#include "circle.h"
#include "math.h"

static const double kPI = 4 * atan(1.0);

double Circle::GetArea() const {
  return kPI * radius_ * radius_;
}

std::string Circle::NameOf() const {
  return DefaultNameOf();
}
