#include <gtest/gtest.h>

#include "common.h"
#include "under_attack_wrapper.h"

using namespace ec;

class UnderAttackWrapperTest : public ::testing::Test {
 protected:
  //  void SetUp() override {}
  // void TearDown() override {}

  UnderAttackWrapper uaw;

};

TEST_F(UnderAttackWrapperTest, UnderAttackOnPhysicalWorks) {
  int real_damage_value = 0;

  real_damage_value = uaw.UnderAttackOnPhysical(kPhysical, kJunior, 10);
  EXPECT_EQ(real_damage_value, 10);

  real_damage_value = uaw.UnderAttackOnPhysical(kPhysical, kIntermediate, 10);
  EXPECT_EQ(real_damage_value, 10);

  real_damage_value = uaw.UnderAttackOnPhysical(kPhysical, kSenior, 10);
  EXPECT_EQ(real_damage_value, 10);

  real_damage_value = uaw.UnderAttackOnPhysical(kMagic, kJunior, 10);
  EXPECT_EQ(real_damage_value, 40);

  real_damage_value = uaw.UnderAttackOnPhysical(kMagic, kIntermediate, 10);
  EXPECT_EQ(real_damage_value, 30);

  real_damage_value = uaw.UnderAttackOnPhysical(kMagic, kSenior, 10);
  EXPECT_EQ(real_damage_value, 20);
}

TEST_F(UnderAttackWrapperTest, UnderAttackOnMagicWorks) {
  int real_damage_value = 0;

  real_damage_value = uaw.UnderAttackOnMagic(kMagic, kJunior, 10);
  EXPECT_EQ(real_damage_value, 10);

  real_damage_value = uaw.UnderAttackOnMagic(kMagic, kIntermediate, 10);
  EXPECT_EQ(real_damage_value, 10);

  real_damage_value = uaw.UnderAttackOnMagic(kMagic, kSenior, 10);
  EXPECT_EQ(real_damage_value, 10);

  real_damage_value = uaw.UnderAttackOnMagic(kPhysical, kJunior, 10);
  EXPECT_EQ(real_damage_value, 40);

  real_damage_value = uaw.UnderAttackOnMagic(kPhysical, kIntermediate, 10);
  EXPECT_EQ(real_damage_value, 30);

  real_damage_value = uaw.UnderAttackOnMagic(kPhysical, kSenior, 10);
  EXPECT_EQ(real_damage_value, 20);
}
