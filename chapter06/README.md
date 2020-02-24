[TOC]

## Inheritance and Object-Oriented Design

### Rule32: Make sure public inheritance models "is-a".

q:如何理解is-a?
>public inheritance意味着is-a，详细点来说，即适用于
base class身上的每一件事情(注意，是每一件事情),都适用于derived class.
否则，不能用public inheritance来描述classes之间的关系

q:对于is-a，作者都举了哪些例子？
>rectange和square的例子，令人映像深刻。主观的直觉在继承体系当中一定要小心，
正方形是矩形，这是有严格数学证明的。没有任何问题。但是我们如果用is-a关系
来描述正方形和矩形的关系，显然会失败。比如矩形可以单独增加width或者height，
但是对于正方形，显然这个方法不满足，因此，不能用is-a来进行构造

q:是否rectange和square就一定不能用is-a来构造呢？
>不是。不存在完美设计，只存在最佳设计。一定要具体问题，具体分析。
假如我们构造类之间的关系时，只考虑面积，那么可以用is-a来构造
square和rectangle之间的关系。is-a只是提醒我们，base class的所有行为
都适用于派生类，但是base class本身要定义哪些行为，需要具体问题，具体分析

### Rule33: Avoid hiding inherited names.

- demo-01: 一个正确的例子
- demo-02: 一个错误的例子(虚函数和非虚函数进行重载，导致hidding inherited names)
- demo-03: 尝试进行修正
- demo-04: demo-04和demo-03的区别在于前者一个纯虚函数一个虚函数，后者两个都是虚函数

q:name-hiding rules一个非常重要的原则是什么?
>名称的类型，并不重要。

```cpp
// ...
int x;
void foo {
  double x;
  std::cin >> x;
}
```

q:hiding inherited name会导致什么问题?
>会导致inherited names不可见，从而不可访问。这就违背了Rule 32，
即派生类不具备基类的某些行为，此时derived is not a base.

```cpp
// base.h
#ifndef BASE_H_
#define BASE_H_

class Base {
 public:
  Base() {}
  virtual ~Base() {}

 public:
  virtual void mf1() = 0;
  virtual void mf1(int);
  virtual void mf2();
  void mf3();
  void mf3(double);

};

#endif

// derived.h
#ifndef DERIVED_H_
#define DERIVED_H_

#include "base.h"

class Derived : public Base {
 public:
  Derived() : Base() {}

 public:
  void mf1() override;
  void mf3();
  void mf4();
};

#endif

// main.cc
#include "derived.h"

int main(void) {
  Derived a_derived;

  a_derived.mf1();
  a_derived.mf1(3);

  a_derived.mf2();

  a_derived.mf3();
  a_derived.mf3(1.0);

  a_derived.mf4();

  return 0;
}

/*
g++ -std=c++11 -g -Wall -Wextra    -c -o main.o main.cc
main.cc:7:13: error: too many arguments to function call, expected 0, have 1; did you mean 'Base::mf1'?
  a_derived.mf1(3);
            ^~~
            Base::mf1
./base.h:11:16: note: 'Base::mf1' declared here
  virtual void mf1(int);
               ^
main.cc:12:13: error: too many arguments to function call, expected 0, have 1; did you mean 'Base::mf3'?
  a_derived.mf3(1.0);
            ^~~
            Base::mf3
./base.h:14:8: note: 'Base::mf3' declared here
  void mf3(double);
       ^
2 errors generated.
make: *** [main.o] Error 1
*/
```

q:how to avoid hiding inherited names?
>effective cpp只说了不要这么做，但是如何改进没有说。
msdn给了建议，Dont't do this.(即在派生类当中对于基类的函数进行redefinition.)
>Here are some basic differences:

>An overloaded function is a function that shares its name with one or more other functions, but which has a different parameter list. The compiler chooses which function is desired based upon the arguments used.

>An overridden function is a method in a descendant class that has a different definition than a virtual function in an ancestor class. The compiler chooses which function is desired based upon the type of the object being used to call the function.

>A redefined function is a method in a descendant class that has a different definition than a non-virtual function in an ancestor class. Don't do this. Since the method is not virtual, the compiler chooses which function to call based upon the static type of the object reference rather than the actual type of the object.

q:对于non-virtual functions，我们通过在派生类当中不进行redefinition可以避免hiding inherited names。但是一个virtual function，如果在基类当中进行了重载，派生了如何避免这个问题？
>采用using declaration,对基类当中符号，在派生类当中进行声明。
不过，我目前到没有见到过，特别必要的需要在基类中对虚函数进行重载的，并且派生类只重写其中某一个。
从我目前的经验来看，尽量还是避免这样的语义

```cpp
// demo-03
// base.h
#ifndef BASE_H_
#define BASE_H_

class Base {
 public:
  Base() {}
  virtual ~Base() {}

 public:
  virtual void mf1() = 0;
  virtual void mf1(int);
  virtual void mf2();
  void mf3();
  void mf3(double);

};

#endif

// derived.h
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

// main.cc
#include "derived.h"

int main(void) {
  Derived a_derived;

  a_derived.mf1();
  a_derived.mf1(3);

  a_derived.mf2();

  a_derived.mf3();
  a_derived.mf3(1.0);

  a_derived.mf4();

  return 0;
}

/*
Derived::mf1() called.
Base::mf1(int) called. x = 3
Base::mf2() called.
Base::mf3() called.
Base::mf3(double) called. x = 1
Derived::mf4() called.
*/
```

总结：
- non-virtual functions在基类中重载，派生类不进行redefinition
- virtual functions(pure and impure)在基类中重载，派生类声明需要重写的。不重写的通过using进行声明
- 以上两种方法，均是为了avoid inheritated hidding names.
