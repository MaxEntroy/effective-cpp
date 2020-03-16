#ifndef WARLOCK_H_
#define WARLOCK_H_

#include <string>

#include "game_character.h"

namespace ec {

class Warlock : public GameCharacter {
 public:
  Warlock() : GameCharacter() {}
  Warlock(int hv, CharacterLevel level, PtrUnderAttack attack_ptr, const std::string& g)
    : GameCharacter(hv, level, attack_ptr), gender_(g) {}

 public:
  std::string gender() const {return gender_;}
  void set_gender(const std::string& g) {gender_ = g;}

 private:
  std::string gender_;
};

} // namespace ec

#endif // WARLOCK_H_
