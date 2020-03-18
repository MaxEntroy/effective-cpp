#include <iostream>

#include "circle.h"

using namespace ec;

int main(void) {
  Shape* p = new Circle();

  std::cout << p->NameOf() << std::endl;
  p->Draw();
  p->Draw(kBlue);

  return 0;
}
