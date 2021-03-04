#ifndef WARLOCK_H_
#define WARLOCK_H_

#include "game_character.h"

namespace ec {

class Warlock : public GameCharacter {
 public:
   Warlock() : GameCharacter() {}
   Warlock(int hv, CharacterLevel level) : GameCharacter(hv, level) {}

 public:
   void UnderAttack(DamageType damage_type, int damage_value) override;
};

} // namespace ec

#endif // WARLOCK_H_
