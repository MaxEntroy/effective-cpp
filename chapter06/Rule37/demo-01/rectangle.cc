#include "rectangle.h"

#include <iostream>

namespace ec {

std::string Rectangle::NameOf() const {
  return "This is a rectangle.";
}

void Rectangle::Draw(Color color) const {
  std::string color_str;
  switch(color) {
    case kRed : {color_str = "red"; break;}
    case kYellow: {color_str = "yellow"; break;}
    case kBlue: {color_str = "blue"; break;}
  }
  std::cout << "Draw a " << color_str << " rectangle." << std::endl;
}

} // namespace ec
