#include "game_character.h"
#include <iostream>

namespace ec {

void GameCharacter::DoUnderAttack(DamageType damage_type, int damage_value) {
  std::cout << "Before DoUnderAttack, hv is " << hv_ << std::endl;
  hv_ -= attack_ptr_->CalRealDamage(damage_type, level_, damage_value);
  std::cout << "After DoUnderAttack, hv is " << hv_ << std::endl;
}

} // namespace ec
