[TOC]
## Rule37: Never redefine a function's inherited default parameter value

### 结论
  
- 只能继承virtual和non-virtual函数，但是Rule36表明不能对non-virtual函数进行重定义，所以只涉及virtual function.
- 对于带有default parameter value的virtual function在进行override时(其实virtual function不存在redefine)，不能重新定义一个新的default parameter value
    - virtual function系dynamic binding,但是default paramter value确实static binding
    - 这回导致虚函数行为分裂，函数执行逻辑是派生类的，但是默认参数列表则是继承基类的(派生类重写的不起作用)

### 问题

考虑如下一组设计，

1. 基类声明vf with default parameter value
2. 派生类进行override时，重定义default parameter value

```cpp
// shape.h
#ifndef SHAPE_H_
#define SHAPE_H_

#include <string>

namespace ec {

enum Color {
  kRed,
  kYellow,
  kBlue
};

class Shape {
 public:
  virtual ~Shape() {}

 public:
  virtual std::string NameOf() const = 0;
  virtual void Draw(Color color = kRed) const = 0;
};

} // namespace ec

#endif // SHAPE_H_

// circle.h
#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "shape.h"

namespace ec {

class Circle : public Shape {
 public:
   Circle() : radius_(1.0) {}
   explicit Circle(double r) : radius_(r) {}

public:
   void set_radius(double r) {radius_ = r;}
   double radius() const {return radius_;}

 public:
  std::string NameOf() const override;
  void Draw(Color color = kYellow) const override; // 重新定义默认列表

 private:
  double radius_;
};

} // namespace ec

#endif // CIRCLE_H_

// circle.cc
#include "circle.h"

#include <iostream>

namespace ec {

std::string Circle::NameOf() const {
  return "This is a circle.";
}

void Circle::Draw(Color color) const {
  std::string color_str;
  switch(color) {
    case kRed : {color_str = "red"; break;}
    case kYellow: {color_str = "yellow"; break;}
    case kBlue: {color_str = "blue"; break;}
  }
  std::cout << "Draw a " << color_str << " circle." << std::endl;
}

} // namespace ec

// main.cc
void test_circle() {
  Shape* p = new Circle;

  std::cout << p->NameOf() << std::endl;
  p->Draw();
  p->Draw(kBlue);

  delete p;
}

/*
This is a circle.
Draw a red circle. // 函数执行体是派生类，但是默认参数确是基类
Draw a blue circle.
*/
```


### 解决

#### 派生类不修改声明

- 手法
  - 既然不允许派生类重定义参数列表，不定义即可

- 优点
  - 没有显著优点，保持接口一致

- 缺点
  - 代码重复造成依赖问题。如果基类修改了虚函数的默认参数，那么所有派生类都需要修改。否则，会违反该规则

```cpp
// shape.h
#ifndef SHAPE_H_
#define SHAPE_H_

#include <string>

namespace ec {

enum Color {
  kRed,
  kYellow,
  kBlue
};

class Shape {
 public:
  virtual ~Shape() {}

 public:
  virtual std::string NameOf() const = 0;
  virtual void Draw(Color color = kRed) const = 0;
};

} // namespace ec

#endif // SHAPE_H_


// rectangle.h
#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "shape.h"

namespace ec {

class Rectangle : public Shape {
 public:
  Rectangle() : width_(1.0), length_(1.0) {}
  Rectangle(double w, double l) : width_(w), length_(l) {}

 public:
  void set_width(double w) {width_ = w;}
  double width() const {return width_;}

  void set_length_(double l) {length_ = l;}
  double length() const {return length_;}

 public:
  std::string NameOf() const override;
  void Draw(Color color = kRed) const override;

 private:
  double width_;
  double length_;
};

} // namespace ec

#endif // RECTANGLE_H_

// main.cc
void test_rectangle() {
  Shape* p = new Rectangle;

  std::cout << p->NameOf() << std::endl;
  p->Draw();
  p->Draw(kBlue);

  delete p;
}

/*
This is a rectangle.
Draw a red rectangle.
Draw a blue rectangle.
*/
```

#### NVI idiom

- 手法
  - non-virtual负责指定默认参数(non-virtual函数继承语义体现强制实现，接口的不变性)
  - vf执行真正的工作

- 优点
  - 避免代码重复依赖性

- 缺点
  - NVI手法的缺点

- 实现

```cpp
// shape.h
#ifndef SHAPE_H_
#define SHAPE_H_

#include <string>

namespace ec {

enum Color {
  kRed,
  kYellow,
  kBlue
};

class Shape {
 public:
  virtual ~Shape() {}

 public:
  virtual std::string NameOf() const = 0;
  void Draw(Color color = kRed);

 private:
  virtual void DoDraw(Color color) const = 0;
};

} // namespace ec

#endif // SHAPE_H_

// circle.h
#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "shape.h"

namespace ec {

class Circle : public Shape {
 public:
   Circle() : radius_(1.0) {}
   explicit Circle(double r) : radius_(r) {}

 public:
   void set_radius(double r) {radius_ = r;}
   double radius() const {return radius_;}

 public:
  std::string NameOf() const override;

 private:
  void DoDraw(Color color) const override;

 private:
  double radius_;
};

} // namespace ec


#endif // CIRCLE_H_
```