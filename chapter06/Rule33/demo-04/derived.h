#ifndef DERIVED_H_
#define DERIVED_H_

#include "base.h"

class Derived : public Base {
 public:
  Derived() : Base() {}

 public:
  using Base::mf1;
  void mf1() override;
  void mf4();
};

#endif
