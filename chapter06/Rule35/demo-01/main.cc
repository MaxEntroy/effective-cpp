#include <iostream>

#include "warrior.h"
#include "warlock.h"

using namespace ec;

int main(void) {

  Warrior a(100, kJunior);
  a.UnderAttack(kPhysical, 10);
  std::cout << a.hv() << std::endl;

  a.UnderAttack(kMagic, 10);
  std::cout << a.hv() << std::endl;

  Warlock b(100, kJunior);
  b.UnderAttack(kMagic, 10);
  std::cout << b.hv() << std::endl;

  b.UnderAttack(kPhysical, 10);
  std::cout << b.hv() << std::endl;

  return 0;
}
