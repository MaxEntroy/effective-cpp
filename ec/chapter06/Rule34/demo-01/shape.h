#ifndef SHAPE_H_
#define SHAPE_H_

#include <stdint.h>
#include <string>

class Shape {
 public:
  virtual ~Shape() {}

 public:
  virtual double GetArea() const = 0;
  virtual std::string NameOf() const;
  uint32_t ObjectId() const;
};

#endif
