#include <iostream>

#include "warrior.h"

using namespace ec;

int main(void) {

  Warrior a(100, kJunior);
  a.UnderAttack(kPhysical, 10);
  std::cout << a.hv() << std::endl;

  a.UnderAttack(kMagic, 10);
  std::cout << a.hv() << std::endl;

  return 0;
}
