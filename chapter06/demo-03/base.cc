#include "base.h"

#include <iostream>

void Base::mf1(int x) {
  std::cout << "Base::mf1(int) called. x = " << x << "\n";
}

void Base::mf2() {
  std::cout << "Base::mf2() called.\n";
}

void Base::mf3() {
  std::cout << "Base::mf3() called.\n";
}

void Base::mf3(double x) {
  std::cout << "Base::mf3(double) called. x = " << x << "\n";
}
