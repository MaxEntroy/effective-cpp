#ifndef DERIVED_H_
#define DERIVED_H_

#include "base.h"

class Derived : public Base {
 public:
  Derived() : Base() {}

 public:
  using Base::mf1; // using  declaration
  void mf1() override;
  // void mf3(); // avoid hidding inherited names
  void mf4();
};

#endif
