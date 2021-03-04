[TOC]
## Rule38: Model "has-a" or "is-implementated-in-terms-of" through composition.

### Outline

- composition
    - has-a
        - application domain
        - 概念关系
    - is-implementated-in-terms-of
        - implementation domain
        - 更类似一种组件关系

### is-a vs is-implemented-in-terms-of

比较麻烦的是区分is-a和is-implementated-in-terms-of这两种对象关系。我们来看一个书上讲的例子。
考虑这样一个问题。

q:假设你希望自己实现一个set，应该如何实现?
>显然的做法是复用，std::set<>是首选，没有必要自己实现。
>
>但是，目前问题是，stl的实现为了保证对数时间(logarithmic-time)通常采用bst实现，所以在空间上做了额外的开销。
如果此时更看重空间，而不是时间，那么就需要自己实现

#### 错误的做法

q:思路？
>显然，我们了解到底层可以用std::list来实现，用以保证空间效率。那么自然的想法，继承自这个类即可，那么这个类的方法自然为我所用。
>
>但是，public inheritance表达的是一种"is-a"关系，那么我们需要判断下std::set和std::list是否是这样一种关系。
显然不是，std::list允许两个相同的元素存在。但是std::set显然不允许。
当然，我们考虑正方形与矩形的关系(概念上是继承，但实际方法上不是)，也要类似考虑这2者的关系。即需要从实际类的行为上来考虑。
std::list当中的push_front方法，派生类显然可以使用。但是如果连续调用push_front(2)，这个行为是合理的。但是和set语义冲突。
所以，采用public inheritance显然是不对的。

```cpp
// set.h
#ifndef SET_H_
#define SET_H_

#include <algorithm>
#include <list>

namespace ec {

template<class T>
class Set : public std::list<T> {
 public:
  typedef std::list<T> Base;

  bool Member(const T& item) const;
  void Insert(const T& item);
  void Remove(const T& item);
  std::size_t Size() const;
};

template<class T>
bool Set<T>::Member(const T& item) const {
  return std::find(Base::begin(), Base::end(), item) != Base::end();
}

template<class T>
void Set<T>::Insert(const T& item) {
  Base::insert(Base::begin(), item);
}

template<class T>
void Set<T>::Remove(const T& item) {
  Base::remove(item);
}

template<class T>
std::size_t Set<T>::Size() const {
  return Base::size();
}

} // namespace ec

#endif // SET_H_
```

上面这段代码暴露的一些问题：
1. 显然，既然是public inheritance，那么Set当中自然继承了push_front,push_back等方法，可以自由使用。但此时破坏set元素唯一性
2. 模板类头文件和源文件不能分离
3. Member函数起初实现时，不知道如何获取基类的存储数据的部分。但是后来想到容器，迭代器，算法三者关系，想明白应该通过迭代器来解决这个问题

#### 正确的做法

q:思路？
>既然set和list不是is-a的关系，应该是set is implemented in terms of list.
所以，采用composition解决这个问题

```cpp
// set.h
#ifndef SET_H_
#define SET_H_

#include <algorithm>
#include <list>

namespace ec {

template<class T>
class Set {
 public:
   Set() {}

 public:
   bool Member(const T& item) const;
   void Insert(const T& item);
   void Remove(const T& item);
   std::size_t Size() const;

 private:
  std::list<T> l_;
};

template<class T>
bool Set<T>::Member(const T& item) const {
  return std::find(l_.begin(), l_.end(), item) != l_.end();
}

template<class T>
void Set<T>::Insert(const T& item) {
  l_.insert(l_.begin(), item);
}

template<class T>
void Set<T>::Remove(const T& item) {
  l_.remove(item);
}

template<class T>
std::size_t Set<T>::Size() const {
  return l_.size();
}

} // namespace ec

#endif // SET_H_
```