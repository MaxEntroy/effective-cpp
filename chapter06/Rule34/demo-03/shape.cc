#include "shape.h"

#include <time.h>

std::string Shape::NameOf() const {
  return "This is a Shape.";
}

uint32_t Shape::ObjectId() const {
  return (uint32_t)time(NULL);
}
