#include <gtest/gtest.h>

#include "warrior.h"
#include "under_attack_wrapper.h"

using namespace ec;

class WarriorTest : public ::testing::Test {
 protected:
  void SetUp() override {
    w1.set_hv(100);
    w1.set_level(kJunior);
    w1.set_do_under_attack(std::bind(&UnderAttackWrapper::UnderAttackOnPhysical, &uaw, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    w1.set_age(20);

    w2.set_hv(100);
    w2.set_level(kIntermediate);
    w2.set_do_under_attack(std::bind(&UnderAttackWrapper::UnderAttackOnPhysical, &uaw, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    w2.set_age(21);

    w3.set_hv(100);
    w3.set_level(kSenior);
    w3.set_do_under_attack(std::bind(&UnderAttackWrapper::UnderAttackOnPhysical, &uaw, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    w3.set_age(22);
  }
  // void TearDown() override {}

  // Declare any objects you plan to use
  UnderAttackWrapper uaw;
  Warrior w0;
  Warrior w1;
  Warrior w2;
  Warrior w3;
};

TEST_F(WarriorTest, HvWorks) {
  EXPECT_EQ(w0.hv(), 0);
  EXPECT_EQ(w1.hv(), 100);
  EXPECT_EQ(w2.hv(), 100);
  EXPECT_EQ(w3.hv(), 100);
}

TEST_F(WarriorTest, LevelWorks) {
  EXPECT_EQ(w0.level(), kJunior);
  EXPECT_EQ(w1.level(), kJunior);
  EXPECT_EQ(w2.level(), kIntermediate);
  EXPECT_EQ(w3.level(), kSenior);
}

TEST_F(WarriorTest, DoUnderAttackWorks) {
  EXPECT_EQ(w0.do_under_attack(), nullptr);
}

TEST_F(WarriorTest, AgeWorks) {
  EXPECT_EQ(w0.age(), 0);
  EXPECT_EQ(w1.age(), 20);
  EXPECT_EQ(w2.age(), 21);
  EXPECT_EQ(w3.age(), 22);
}

TEST_F(WarriorTest, SetHvWorks) {
  w0.set_hv(200);
  EXPECT_EQ(w0.hv(), 200);
}

TEST_F(WarriorTest, SetLevelWorks) {
  w0.set_level(kSenior);
  EXPECT_EQ(w0.level(), kSenior);
}

TEST_F(WarriorTest, SetDoUnderAttack) {
  w1.set_do_under_attack(nullptr);
  EXPECT_EQ(w1.do_under_attack(), nullptr);
}

TEST_F(WarriorTest, SetAgeWorks) {
  w0.set_age(20);
  EXPECT_EQ(w0.age(), 20);
}

TEST_F(WarriorTest, UnderAttackWithPhysical) {
  w1.UnderAttack(kPhysical, 10);
  EXPECT_EQ(w1.hv(), 90);

  w2.UnderAttack(kPhysical, 20);
  EXPECT_EQ(w2.hv(), 80);

  w3.UnderAttack(kPhysical, 30);
  EXPECT_EQ(w3.hv(), 70);
}

TEST_F(WarriorTest, UnderAttackWithMagic) {
  w1.UnderAttack(kMagic, 10);
  EXPECT_EQ(w1.hv(), 60);

  w2.UnderAttack(kMagic, 10);
  EXPECT_EQ(w2.hv(), 70);

  w3.UnderAttack(kMagic, 10);
  EXPECT_EQ(w3.hv(), 80);
}
