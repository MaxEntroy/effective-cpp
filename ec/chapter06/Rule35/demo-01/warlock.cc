#include "warlock.h"

namespace ec {

static const int kJuniorPhysicalDamage = 10;
static const int kIntermediatePhysicalDamage = 20;
static const int kSeniorPhysicalDamage = 30;

void Warlock::UnderAttack(DamageType damage_type, int damage_value) {
  if(damage_type == kMagic) {
    hv_ -= damage_value;
  }
  else {
    switch(level_) {
      case kJunior: {
        hv_ -= damage_value + kSeniorPhysicalDamage;
        break;
      }
      case kIntermediate: {
        hv_ -= damage_value + kIntermediatePhysicalDamage;
        break;
      }
      case kSenior: {
        hv_ -= damage_value + kJuniorPhysicalDamage;
        break;
      }
    }
  }
}

} // namespace ec
