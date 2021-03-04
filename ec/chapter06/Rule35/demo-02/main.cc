#include <iostream>

#include "warrior.h"
#include "warlock.h"

using namespace ec;

int main(void) {

  Warrior a(100, kJunior);
  a.UnderAttack(kPhysical, 10);

  a.UnderAttack(kMagic, 10);

  Warlock b(100, kJunior);
  b.UnderAttack(kMagic, 10);

  b.UnderAttack(kPhysical, 10);

  return 0;
}
