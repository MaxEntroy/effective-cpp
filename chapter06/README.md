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

### Rule34: Differentiate between inheritance of interface and inheritance of implementation.

- demo-05: 一个完整的例子, pure virtual, impure virtual, non-virtual
- demo-06: 解决impure virtual的接口和缺省实现分离，提供了一种方法
- demo-07: 同demo-06，提供了另一种方法

q:public继承由那两部分组成？
- function interface inheritance
- functin implementation inheritance

q:derived class当中的继承语义有哪些？
- 只继承函数接口
- 同时继承函数接口和实现，并能进行重写
- 同时继承函数接口和实现，不允许重写

q:c++当中是如何通过语法特性来支持上述继承语义的？
- 声明一个pure virtual function的目的，让derived class只继承其接口
  - pure virtual function在base class(abstract class)中无定义
  - derived class需要给出一个实现
- 声明一个impure virtual function的目的，让derived class继承其接口和缺省实现
  - impure virtual function在base class当中的实现为缺省实现(default implementation)
  - derived class可以给出自己的实现，也可以采用base class当中的缺省实现
- 声明一个non-virtual function的目的，让derived class继承接口和强制性实现

**总结：pure virtual function, impure virtual function, non-virtual function之间的差异，使你可以精确指定
你想derived class继承的东西，只继承接口，或者是继承接口和一份缺省实现，或者是继承接口和一份强制实现。**

ps: 暂时不用考虑virtual function的成本问题

q:Rule34对于缺省行为的讨论想表达什么?
>对于缺省行为，会存在这样的一个问题，就是derived class有能力重写impure function提供的缺省行为。
但是，可能会忘了重写。从而使用缺省行为导致意想不到的结果。
因为这个问题在compile time也无法发现，只有run time才会

```cpp
// shape.h
#ifndef SHAPE_H_
#define SHAPE_H_

#include <stdint.h>
#include <string>

class Shape {
 public:
  virtual ~Shape() {}

 public:
  virtual double GetArea() const = 0;
  virtual std::string NameOf() const;
  uint32_t ObjectId() const;
};

#endif

// circle.h
#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "shape.h"

// circle.h
// 遗漏了对于NameOf的override
class Circle : public Shape {
 public:
  Circle() {}
  explicit Circle(double r) : radius_(r) {}

 public:
  double GetArea() const override;

 private:
  double radius_;
};

#endif

// rectangle.h
#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "shape.h"

class Rectangle : public Shape {
 public:
  Rectangle() {}
  Rectangle(double l, double w) : length_(l), width_(w) {}

 public:
  double GetArea() const override;
  std::string NameOf() const override;

 private:
  double length_;
  double width_;
};

#endif

// triangle.h
#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "shape.h"

class Triangle : public Shape {
 public:
  Triangle() {}
  Triangle(double l, double w) : length_(l), height_(w) {}

 public:
  double GetArea() const override;
  std::string NameOf() const override;

 private:
  double length_;
  double height_;
};

#endif

// main.cc
#include <iostream>

#include "shape.h"
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"

void Show(Shape*);

int main() {
  Shape* p_arr[] = {new Circle(1.0), new Rectangle(1.0, 1.0), new Triangle(1.0, 1.0)};
  int sz = sizeof(p_arr)/sizeof(p_arr[0]);

  for(int i = 0; i < sz; ++i) {
    Show(p_arr[i]);
    delete p_arr[i];
  }

  return 0;
}

void Show(Shape* p) {
  std::cout << "id: " << p->ObjectId()
    << ", name: " << p->NameOf()
    << ", area: " << p->GetArea()
    << "\n";
}

/*
id: 1582641291, name: This is a shape., area: 3.14159
id: 1582641291, name: This is a rectangle., area: 1
id: 1582641291, name: This is a circle., area: 0.5
*/
```

从上面结果可以看出，对于impure function提供的接口和缺省实现，存在派生类忘记重写缺省实现的可能。
从语法上怎么能彻底避免呢？

- 切断impure virtuan function, interface和default implementation.即把接口和缺省实现区别开

```cpp
// shape.h
#ifndef SHAPE_H_
#define SHAPE_H_

#include <stdint.h>
#include <string>

class Shape {
 public:
  virtual ~Shape() {}

 public:
  virtual double GetArea() const = 0;
  virtual std::string NameOf() const = 0;
  uint32_t ObjectId() const;

 protected:
  std::string DefaultNameOf() const;
};

#endif

/*
main.cc:11:25: error: allocating an object of abstract class type 'Circle'
  Shape* p_arr[] = {new Circle(1.0), new Rectangle(1.0, 1.0), new Triangle(1.0, 1.0)};
                        ^
./shape.h:13:23: note: unimplemented pure virtual method 'NameOf' in 'Circle'
  virtual std::string NameOf() const = 0;
                      ^
main.cc:12:18: error: invalid application of 'sizeof' to an incomplete type 'Shape *[]'
  int sz = sizeof(p_arr)/sizeof(p_arr[0]);
                 ^~~~~~~
2 errors generated.
make: *** [main.o] Error 1
*/
```

此时再编译，我们能看到circle因为没有重写NameOf而导致该类任然是抽象类，无法定义对象。从而暴露了忘记重写这个问题。

```cpp
// shape.h
#ifndef SHAPE_H_
#define SHAPE_H_

#include <stdint.h>
#include <string>

class Shape {
 public:
  virtual ~Shape() {}

 public:
  virtual double GetArea() const = 0;
  virtual std::string NameOf() const = 0;
  uint32_t ObjectId() const;

 protected:
  std::string DefaultNameOf() const;
};

#endif

// shape.cc
#include "shape.h"

#include <time.h>

std::string Shape::DefaultNameOf() const {
  return "This is a shape.";
}

uint32_t Shape::ObjectId() const {
  return (uint32_t)time(NULL);
}

// circle.h
#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "shape.h"

class Circle : public Shape {
 public:
  Circle() {}
  explicit Circle(double r) : radius_(r) {}

 public:
  double GetArea() const override;
  std::string NameOf() const override;

 private:
  double radius_;
};

#endif

// circle.cc
#include "circle.h"
#include "math.h"

static const double kPI = 4 * atan(1.0);

double Circle::GetArea() const {
  return kPI * radius_ * radius_;
}

std::string Circle::NameOf() const {
  return DefaultNameOf();
}

// triangle.h
#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "shape.h"

class Triangle : public Shape {
 public:
  Triangle() {}
  Triangle(double l, double w) : length_(l), height_(w) {}

 public:
  double GetArea() const override;
  std::string NameOf() const override;

 private:
  double length_;
  double height_;
};

#endif

// triangle.cc
#include "triangle.h"

double Triangle::GetArea() const {
  return 1.0 / 2 * length_ * height_;
}

std::string Triangle::NameOf() const {
  return "This is a triangle.";
}
```

我们从circle.cc和triangle.cc对于NameOf()的实现上能看出来，如果想用缺省的，使用base当中提供的缺省即可。否则自己定义。
这样肯定不会出现忘了重定义的问题，因为pure virtual function，要求你必须要实现。

- 还是同样的办法，分离接口和缺省实现

上面的这个办法，也不错，但是有人觉得需要单独提供一个方法，会导致过度雷同的函数名，进一步导致class命名空间污染的问题。
解决办法是，pure virtual function自己提供一个实现，是不是听起来有一点奇怪，pure virtual function居然有定义。
但是需要肯定的是，如果为pure virtual function定义了实现，调用时必须采用explicit qualifying.

```cpp
// shape.h
#ifndef SHAPE_H_
#define SHAPE_H_

#include <stdint.h>
#include <string>

class Shape {
 public:
  virtual ~Shape() {}

 public:
  virtual double GetArea() const = 0;
  virtual std::string NameOf() const = 0;
  uint32_t ObjectId() const;
};

#endif

// shape.cc
#include "shape.h"

#include <time.h>

std::string Shape::NameOf() const {
  return "This is a Shape.";
}

uint32_t Shape::ObjectId() const {
  return (uint32_t)time(NULL);
}

// circle.h
#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "shape.h"

class Circle : public Shape {
 public:
  Circle() {}
  explicit Circle(double r) : radius_(r) {}

 public:
  double GetArea() const override;
  std::string NameOf() const override;

 private:
  double radius_;
};

#endif

// circle.cc
#include "circle.h"
#include "math.h"

static const double kPI = 4 * atan(1.0);

double Circle::GetArea() const {
  return kPI * radius_ * radius_;
}

std::string Circle::NameOf() const {
  return Shape::NameOf();
}
```