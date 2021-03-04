#ifndef WARLOCK_H_
#define WARLOCK_H_

#include <string>

#include "game_character.h"

namespace ec {

class Warlock : public GameCharacter {
 public:
  Warlock() : GameCharacter() {}
  Warlock(int hv, CharacterLevel level, DoUnderAttackFunc func, const std::string& g)
    : GameCharacter(hv, level, func), gender_(g) {}

 public:
  std::string gender() const {return gender_;}
  void set_gender(const std::string& g) {gender_ = g;}

 private:
  std::string gender_;
};

} // namespace ec

#endif // WARLOCK_H_
