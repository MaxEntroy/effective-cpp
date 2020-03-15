#include "under_attack_wrapper.h"

namespace ec {

static const int kJuniorMagicDamage = 10;
static const int kIntermediateMagicDamage = 20;
static const int kSeniorMagicDamage = 30;

static const int kJuniorPhysicalDamage = 10;
static const int kIntermediatePhysicalDamage = 20;
static const int kSeniorPhysicalDamage = 30;

int UnderAttackWrapper::UnderAttackOnPhysical(DamageType damage_type,
                                              CharacterLevel level,
                                              int damage_value) {
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

int UnderAttackWrapper::UnderAttackOnMagic(DamageType damage_type,
                                           CharacterLevel level,
                                           int damage_value) {
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
