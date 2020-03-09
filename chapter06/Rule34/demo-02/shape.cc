#include "shape.h"

#include <time.h>

std::string Shape::DefaultNameOf() const {
  return "This is a shape.";
}

uint32_t Shape::ObjectId() const {
  return (uint32_t)time(NULL);
}
