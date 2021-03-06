#ifndef GAME_CHARACTER_H_
#define GAME_CHARACTER_H_

#include <functional>

#include "common.h"

namespace ec {

class GameCharacter {
 public:
  typedef std::function<int(DamageType, CharacterLevel, int)> DoUnderAttackFunc;

 public:
  GameCharacter() : hv_(0), level_(kJunior), do_under_attack_(nullptr) {}
  GameCharacter(int hv, CharacterLevel level, DoUnderAttackFunc func) : hv_(hv), level_(level), do_under_attack_(func) {}
  virtual ~GameCharacter() {}

 public:
  int hv() const { return hv_; }
  void set_hv(int hv) { hv_ = hv; }

  CharacterLevel level() const { return level_; }
  void set_level(CharacterLevel level) { level_ = level; }

  DoUnderAttackFunc do_under_attack() const {return do_under_attack_;}
  void set_do_under_attack(DoUnderAttackFunc func) {do_under_attack_ = func;}

  // health value is based on:
  // 1. damage type
  // 2. damage value
  // 3. character level
  void UnderAttack(DamageType damage_type, int damage_value);

 protected:
  int hv_;
  CharacterLevel level_;
  DoUnderAttackFunc do_under_attack_;
};

} // namespace ec

#endif // GAME_CHARACTER_H_
