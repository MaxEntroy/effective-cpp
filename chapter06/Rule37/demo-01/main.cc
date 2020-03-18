#include "circle.h"
#include "rectangle.h"

#include <iostream>

using namespace ec;

void test_circle() {
  Shape* p = new Circle;

  std::cout << p->NameOf() << std::endl;
  p->Draw();
  p->Draw(kBlue);

  delete p;
}

void test_rectangle() {
  Shape* p = new Rectangle;

  std::cout << p->NameOf() << std::endl;
  p->Draw();
  p->Draw(kBlue);

  delete p;
}

int main(void) {
  test_circle();
  test_rectangle();
  return 0;
}
