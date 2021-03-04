#ifndef GAME_CHARACTER_H_
#define GAME_CHARACTER_H_

#include "common.h"
#include "under_attack.h"

namespace ec {

class GameCharacter {
 public:
  typedef UnderAttack* PtrUnderAttack;

 public:
  GameCharacter() : hv_(0), level_(kJunior), attack_ptr_(nullptr) {}
  GameCharacter(int hv, CharacterLevel level, PtrUnderAttack attack_ptr) : hv_(hv), level_(level), attack_ptr_(attack_ptr) {}
  virtual ~GameCharacter() {}

 public:
  int hv() const { return hv_; }
  void set_hv(int hv) { hv_ = hv; }

  CharacterLevel level() const { return level_; }
  void set_level(CharacterLevel level) { level_ = level; }

  PtrUnderAttack attack_ptr() const {return attack_ptr_;}
  void set_attack_ptr(PtrUnderAttack attack_ptr) {attack_ptr_ = attack_ptr;}

  // health value is based on:
  // 1. damage type
  // 2. damage value
  // 3. character level
  void DoUnderAttack(DamageType damage_type, int damage_value);

 protected:
  int hv_;
  CharacterLevel level_;
  PtrUnderAttack attack_ptr_;
};

} // namespace ec

#endif // GAME_CHARACTER_H_
