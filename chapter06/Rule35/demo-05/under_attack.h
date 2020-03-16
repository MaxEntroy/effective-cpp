#ifndef UNDER_ATTACK_H_
#define UNDER_ATTACK_H_

#include "common.h"

namespace ec {

class UnderAttack {
 public:
  virtual ~UnderAttack() {}

 public:
  virtual int CalRealDamage(DamageType damage_type, CharacterLevel level, int damage_value) const = 0;
};

} // namespace ec

#endif // UNDER_ATTACK_H_
