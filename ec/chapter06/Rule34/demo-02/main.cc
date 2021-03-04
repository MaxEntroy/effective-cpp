#include <iostream>

#include "shape.h"
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"

void Show(Shape*);

int main() {
  Shape* p_arr[] = {new Circle(1.0), new Rectangle(1.0, 1.0), new Triangle(1.0, 1.0)};
  int sz = sizeof(p_arr)/sizeof(p_arr[0]);

  for(int i = 0; i < sz; ++i) {
    Show(p_arr[i]);
    delete p_arr[i];
  }

  return 0;
}

void Show(Shape* p) {
  std::cout << "id: " << p->ObjectId()
    << ", name: " << p->NameOf()
    << ", area: " << p->GetArea()
    << "\n";
}
