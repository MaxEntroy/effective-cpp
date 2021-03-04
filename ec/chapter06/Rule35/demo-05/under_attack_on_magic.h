#ifndef UNDER_ATTACK_ON_MAGIC_H_
#define UNDER_ATTACK_ON_MAGIC_H_

#include "under_attack.h"

namespace ec {

class UnderAttackOnMagic : public UnderAttack {
 public:
  int CalRealDamage(DamageType damage_type, CharacterLevel level, int damage_value) const override;
};

} // namespace ec

#endif // UNDER_ATTACK_ON_MAGIC_H_
