### Rule34: Differentiate between inheritance of interface and inheritance of implementation.

- demo-01: 一个完整的例子, pure virtual, impure virtual, non-virtual
- demo-02: 解决impure virtual的接口和缺省实现分离，提供了一种方法
- demo-03: 同demo-06，提供了另一种方法

**特别注意的是**，rule34本周上是告诉大家不同函数声明的语义是什么，但是一定要特别注意的是，
对于impure virtual functions，作者是建议大家把接口和缺省实现进行分离的。我之前
没有特别注意这一点的是，我觉得这么做相当于没有impure virtual function的存在了，全是pure virtual functions

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