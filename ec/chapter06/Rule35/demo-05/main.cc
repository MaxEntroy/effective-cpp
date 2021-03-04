#include "warrior.h"
#include "warlock.h"
#include "under_attack_on_physical.h"
#include "under_attack_on_magic.h"

using namespace ec;

int main(void) {
  Warrior a(100, kJunior, new UnderAttackOnPhysical(), 20);
  a.DoUnderAttack(kPhysical, 10);

  Warlock b(100, kJunior, new UnderAttackOnMagic(), "male");
  b.DoUnderAttack(kMagic, 10);

  return 0;
}
