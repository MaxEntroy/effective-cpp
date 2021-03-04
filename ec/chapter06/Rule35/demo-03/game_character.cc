#include "game_character.h"

#include <iostream>

namespace ec {

static const int kJuniorMagicDamage = 10;
static const int kIntermediateMagicDamage = 20;
static const int kSeniorMagicDamage = 30;

static const int kJuniorPhysicalDamage = 10;
static const int kIntermediatePhysicalDamage = 20;
static const int kSeniorPhysicalDamage = 30;

void WarriorUnderAttack(GameCharacter* gc, DamageType damage_type,
                        int damage_value) {
  if(damage_type == kPhysical) {
    gc->hv_ -= damage_value;
  }
  else {
    switch(gc->level_) {
      case kJunior: {
        gc->hv_ -= damage_value + kSeniorMagicDamage;
        break;
      }
      case kIntermediate: {
        gc->hv_ -= damage_value + kIntermediateMagicDamage;
        break;
      }
      case kSenior: {
        gc->hv_ -= damage_value + kJuniorMagicDamage;
        break;
      }
    }
  }
}

void WarlockUnderAttack(GameCharacter* gc, DamageType damage_type,
                        int damage_value) {
  if(damage_type == kMagic) {
    gc->hv_ -= damage_value;
  }
  else {
    switch(gc->level_) {
      case kJunior: {
        gc->hv_ -= damage_value + kSeniorPhysicalDamage;
        break;
      }
      case kIntermediate: {
        gc->hv_ -= damage_value + kIntermediatePhysicalDamage;
        break;
      }
      case kSenior: {
        gc->hv_ -= damage_value + kJuniorPhysicalDamage;
        break;
      }
    }
  }
}

void GameCharacter::UnderAttack(DamageType damage_type, int damage_value) {
  std::cout << "Before under attack, hv is " << hv_ << std::endl;
  do_under_attack_(this, damage_type, damage_value);
  std::cout << "After under attack, hv is " << hv_ << std::endl;
}

} // namespace ec
