#ifndef BASE_H_
#define BASE_H_

class Base {
 public:
  Base() {}
  virtual ~Base() {}

 public:
  virtual void mf1() = 0;
  virtual void mf2();
  void mf3();

};

#endif
