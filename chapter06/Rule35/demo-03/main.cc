#include <iostream>

#include "warrior.h"
#include "warlock.h"

using namespace ec;

int main(void) {

  Warrior a(100, kJunior, &WarriorUnderAttack, 20);
  a.UnderAttack(kPhysical, 10);

  Warlock b(100, kJunior, &WarlockUnderAttack, "male");
  b.UnderAttack(kMagic, 10);

  return 0;
}
