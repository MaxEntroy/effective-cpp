#include "circle.h"

#include <iostream>

namespace ec {

std::string Circle::NameOf() const {
  return "This is a circle.";
}

void Circle::Draw(Color color) const {
  std::string color_str;
  switch(color) {
    case kRed : {color_str = "red"; break;}
    case kYellow: {color_str = "yellow"; break;}
    case kBlue: {color_str = "blue"; break;}
  }
  std::cout << "Draw a " << color_str << " circle." << std::endl;
}

} // namespace ec
