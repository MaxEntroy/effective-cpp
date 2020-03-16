#include "under_attack_on_magic.h"

namespace ec {

static const int kJuniorPhysicalDamage = 10;
static const int kIntermediatePhysicalDamage = 20;
static const int kSeniorPhysicalDamage = 30;

int UnderAttackOnMagic::CalRealDamage(DamageType damage_type, CharacterLevel level, int damage_value) const {
  int real_damage_value = 0;
  if(damage_type == kMagic) {
    real_damage_value = damage_value;
  }
  else {
    switch(level) {
      case kJunior: {
        real_damage_value = damage_value + kSeniorPhysicalDamage;
        break;
      }
      case kIntermediate: {
        real_damage_value = damage_value + kIntermediatePhysicalDamage;
        break;
      }
      case kSenior: {
        real_damage_value = damage_value + kJuniorPhysicalDamage;
        break;
      }
    }
  }
  return real_damage_value;
}

} // namespace ec
