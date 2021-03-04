#include "warrior.h"

namespace ec {

static const int kJuniorMagicDamage = 10;
static const int kIntermediateMagicDamage = 20;
static const int kSeniorMagicDamage = 30;

void Warrior::UnderAttack(DamageType damage_type, int damage_value) {
  if(damage_type == kPhysical) {
    hv_ -= damage_value;
  }
  else {
    switch(level_) {
      case kJunior: {
        hv_ -= damage_value + kSeniorMagicDamage;
        break;
      }
      case kIntermediate: {
        hv_ -= damage_value + kIntermediateMagicDamage;
        break;
      }
      case kSenior: {
        hv_ -= damage_value + kJuniorMagicDamage;
        break;
      }
    }
  }
}

} // namespace ec
