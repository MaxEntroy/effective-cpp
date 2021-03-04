#ifndef WARRIOR_H_
#define WARRIOR_H_

#include "game_character.h"

namespace ec {

class Warrior : public GameCharacter {
 public:
  Warrior() : GameCharacter() {}
  Warrior(int hv, CharacterLevel level) : GameCharacter(hv, level) {}

 private:
  void DoUnderAttack(DamageType damage_type, int damage_value) override;
};

} // namespace ec

#endif // WARRIOR_H_
