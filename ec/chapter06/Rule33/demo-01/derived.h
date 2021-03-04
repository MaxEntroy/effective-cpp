#ifndef DERIVED_H_
#define DERIVED_H_

#include "base.h"

class Derived : public Base {
 public:
  Derived() : Base() {}

 public:
  void mf1() override;
  void mf4();
};

#endif
