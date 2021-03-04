#include "under_attack_on_physical.h"

namespace ec {

static const int kJuniorMagicDamage = 10;
static const int kIntermediateMagicDamage = 20;
static const int kSeniorMagicDamage = 30;

int UnderAttackOnPhysical::CalRealDamage(DamageType damage_type, CharacterLevel level, int damage_value) const {
  int real_damage_value = 0;
  if(damage_type == kPhysical) {
    real_damage_value = damage_value;
  }
  else {
    switch(level) {
      case kJunior: {
        real_damage_value = damage_value + kSeniorMagicDamage;
        break;
      }
      case kIntermediate: {
        real_damage_value = damage_value + kIntermediateMagicDamage;
        break;
      }
      case kSenior: {
        real_damage_value = damage_value + kJuniorMagicDamage;
        break;
      }
    }
  }
  return real_damage_value;
}

} // namespace ec
