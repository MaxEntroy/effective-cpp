#include <gtest/gtest.h>
#include "under_attack_on_physical.h"

using namespace ec;

class UnderAttackOnPhysicalTest : public ::testing::Test {
 protected:
  UnderAttackOnPhysical obj;
};

TEST_F(UnderAttackOnPhysicalTest, CalRealDamageWorks) {
  int real_damage_value = 0;

  real_damage_value = obj.CalRealDamage(kPhysical, kJunior, 10);
  EXPECT_EQ(real_damage_value, 10);

  real_damage_value = obj.CalRealDamage(kPhysical, kIntermediate, 10);
  EXPECT_EQ(real_damage_value, 10);

  real_damage_value = obj.CalRealDamage(kPhysical, kSenior, 10);
  EXPECT_EQ(real_damage_value, 10);

  real_damage_value = obj.CalRealDamage(kMagic, kJunior, 10);
  EXPECT_EQ(real_damage_value, 40);

  real_damage_value = obj.CalRealDamage(kMagic, kIntermediate, 10);
  EXPECT_EQ(real_damage_value, 30);

  real_damage_value = obj.CalRealDamage(kMagic, kSenior, 10);
  EXPECT_EQ(real_damage_value, 20);
}
