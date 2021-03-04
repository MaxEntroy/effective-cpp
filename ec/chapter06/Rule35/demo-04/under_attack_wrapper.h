#ifndef UNDER_ATTACK_WRAPPER_H_
#define UNDER_ATTACK_WRAPPER_H_

#include "common.h"

namespace ec {

class UnderAttackWrapper {
 public:
  UnderAttackWrapper() {}

 public:
  // 物理基础伤害
  // 1.物理伤害不加倍
  // 2.魔法伤害根据角色等级加成
  int UnderAttackOnPhysical(DamageType damage_type,
                            CharacterLevel level,
                            int damage_value);

  // 魔法基础伤害
  // 1.魔法伤害不加倍
  // 2.物理伤害根据角色等级加成
  int UnderAttackOnMagic(DamageType damage_type,
                         CharacterLevel level,
                         int damage_value);
};

} // namespace ec

#endif // UNDER_ATTACK_WRAPPER_H_
