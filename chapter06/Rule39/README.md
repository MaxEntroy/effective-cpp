[TOC]
## Rule39: User private inheritance judiously.

### Outline

q:private inheritance的语义是什么？
- private inheritance在"设计"层面(即观念领域)没有任何意义
- private inheritance在"实现"层面(即纯粹是一种实现技术)具有意义：is-implementated-in-terms-of

q:private inheritance vs composition?
- 尽可能使用composition，必要时再使用private inheritance
- 必要时指如下三种情况：
  - protected member。使用composition没有能力访问protected member
  - virtual function。使用composition没有能力override virtual function，因为也不想重新造一个轮子
  - EBO(这是一种激进的情形)

### 实践

#### set is implementated in terms of list

还是上一节的例子，我们来看用private inheritance实现时的一些优缺点

```cpp
#ifndef SET_H_
#define SET_H_

#include <algorithm>
#include <list>

namespace ec {

template<class T>
class Set : private std::list<T> {
 public:
  typedef std::list<T> Base;

  bool Member(const T& val) const;
  void Insert(const T& val);
  void Remove(const T& val);
  std::size_t Size() const;
};

template<class T>
bool Set<T>::Member(const T& val) const {
  return std::find(Base::begin(), Base::end(), val) != Base::end();
}

template<class T>
void Set<T>::Insert(const T& val) {
  Base::insert(Base::begin(), val);
}

template<class T>
void Set<T>::Remove(const T& val) {
  Base::remove(val);
}

template<class T>
std::size_t Set<T>::Size() const {
  return Base::size();
}

} // namespace ec

#endif // SET_H_
```

就本例而言，在实现技巧上composition和private inheritance并无太大区别。但是考虑到private inheritance在设计上并无更多的语义，所以本例应该采用composition进行实现。