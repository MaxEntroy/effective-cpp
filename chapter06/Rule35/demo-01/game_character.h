#ifndef GAME_CHARACTER_H_
#define GAME_CHARACTER_H_

#include "common.h"

namespace ec {

class GameCharacter {
 public:
  GameCharacter() : hv_(0), level_(kJunior) {}
  GameCharacter(int hv, CharacterLevel level) : hv_(hv), level_(level) {}
  virtual ~GameCharacter() {}

 public:
  int hv() const {return hv_;}
  CharacterLevel level() const {return level_;}

  // health value is based on:
  // 1. damage type
  // 2. damage value
  // 3. character level
  virtual void UnderAttack(DamageType damage_type, int damage_value) = 0;

 protected:
  int hv_;
  CharacterLevel level_;
};

} // namespace ec

#endif // GAME_CHARACTER_H_
