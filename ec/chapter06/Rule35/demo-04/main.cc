#include "warrior.h"
#include "warlock.h"
#include "under_attack_wrapper.h"

using namespace ec;

int main(void) {
  UnderAttackWrapper uaw;

  Warrior a(100, kJunior, std::bind(&UnderAttackWrapper::UnderAttackOnPhysical, &uaw, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), 20);
  a.UnderAttack(kPhysical, 10);

  Warlock b(100, kJunior, std::bind(&UnderAttackWrapper::UnderAttackOnMagic, &uaw, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), "male");
  b.UnderAttack(kMagic, 10);

  return 0;
}
