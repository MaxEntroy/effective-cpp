#include "game_character.h"

#include <iostream>

namespace ec {

void GameCharacter::UnderAttack(DamageType damage_type, int damage_value) {
  std::cout << "Before under attack, hv is " << hv_ << std::endl;
  DoUnderAttack(damage_type, damage_value);
  std::cout << "After under attack, hv is " << hv_ << std::endl;
}

} // namespace ec
