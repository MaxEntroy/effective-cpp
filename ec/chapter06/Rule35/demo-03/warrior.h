#ifndef WARRIOR_H_
#define WARRIOR_H_

#include "game_character.h"

namespace ec {

class Warrior : public GameCharacter {
 public:
  Warrior() : GameCharacter(), age_(0) {}
  Warrior(int hv, CharacterLevel level, DoUnderAttackFunc func, int age)
    : GameCharacter(hv, level, func), age_(age) {}

 public:
  int age() const {return age_;}
  void set_age(int a) {age_ = a;}

 private:
  int age_;
};

} // namespace ec

#endif // WARRIOR_H_
