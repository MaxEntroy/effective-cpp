#include <gtest/gtest.h>

#include "warlock.h"
#include "under_attack_on_magic.h"

using namespace ec;

class WarlockTest : public ::testing::Test {
 protected:
  void SetUp() override {
    w1.set_hv(100);
    w1.set_level(kJunior);
    w1.set_attack_ptr(&uam);
    w1.set_gender("male");

    w2.set_hv(100);
    w2.set_level(kIntermediate);
    w2.set_attack_ptr(&uam);
    w2.set_gender("female");

    w3.set_hv(100);
    w3.set_level(kSenior);
    w3.set_attack_ptr(&uam);
    w3.set_gender("male");
  }
  // void TearDown() override {}

  // Declare any objects you plan to use
  UnderAttackOnMagic uam;
  Warlock w0;
  Warlock w1;
  Warlock w2;
  Warlock w3;
};

TEST_F(WarlockTest, HvWorks) {
  EXPECT_EQ(w0.hv(), 0);
  EXPECT_EQ(w1.hv(), 100);
  EXPECT_EQ(w2.hv(), 100);
  EXPECT_EQ(w3.hv(), 100);
}

TEST_F(WarlockTest, LevelWorks) {
  EXPECT_EQ(w0.level(), kJunior);
  EXPECT_EQ(w1.level(), kJunior);
  EXPECT_EQ(w2.level(), kIntermediate);
  EXPECT_EQ(w3.level(), kSenior);
}

TEST_F(WarlockTest, AttackPtrWorks) {
  EXPECT_EQ(w0.attack_ptr(), nullptr);
  EXPECT_EQ(w1.attack_ptr(), &uam);
  EXPECT_EQ(w2.attack_ptr(), &uam);
  EXPECT_EQ(w3.attack_ptr(), &uam);
}

TEST_F(WarlockTest, GenderWorks) {
  EXPECT_EQ(w0.gender(), "");
  EXPECT_EQ(w1.gender(), "male");
  EXPECT_EQ(w2.gender(), "female");
  EXPECT_EQ(w3.gender(), "male");
}

TEST_F(WarlockTest, SetHvWorks) {
  w0.set_hv(200);
  EXPECT_EQ(w0.hv(), 200);
}

TEST_F(WarlockTest, SetLevelWorks) {
  w0.set_level(kSenior);
  EXPECT_EQ(w0.level(), kSenior);
}

TEST_F(WarlockTest, SetDoUnderAttack) {
  w1.set_attack_ptr(nullptr);
  EXPECT_EQ(w1.attack_ptr(), nullptr);
}

TEST_F(WarlockTest, SetGender) {
  w0.set_gender("male");
  EXPECT_EQ(w0.gender(), "male");
}

TEST_F(WarlockTest, DoUnderAttackOnPhysical) {
  w1.DoUnderAttack(kPhysical, 10);
  EXPECT_EQ(w1.hv(), 60);

  w2.DoUnderAttack(kPhysical, 10);
  EXPECT_EQ(w2.hv(), 70);

  w3.DoUnderAttack(kPhysical, 10);
  EXPECT_EQ(w3.hv(), 80);
}

TEST_F(WarlockTest, DoUnderAttackWithMagic) {
  w1.DoUnderAttack(kMagic, 10);
  EXPECT_EQ(w1.hv(), 90);

  w2.DoUnderAttack(kMagic, 10);
  EXPECT_EQ(w2.hv(), 90);

  w3.DoUnderAttack(kMagic, 10);
  EXPECT_EQ(w3.hv(), 90);
}
