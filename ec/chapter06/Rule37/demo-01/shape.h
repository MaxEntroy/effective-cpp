#ifndef SHAPE_H_
#define SHAPE_H_

#include <string>

namespace ec {

enum Color {
  kRed,
  kYellow,
  kBlue
};

class Shape {
 public:
  virtual ~Shape() {}

 public:
  virtual std::string NameOf() const = 0;
  virtual void Draw(Color color = kRed) const = 0;
};

} // namespace ec

#endif // SHAPE_H_
